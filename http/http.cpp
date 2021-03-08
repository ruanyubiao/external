#include "http.h"

#ifndef USE_STANDALONE_ASIO
#define USE_STANDALONE_ASIO 1
#endif

#include <thread>
#include <sstream>
#include "utils/ShareUtils.h"
#include "ThreadPool.h"
#include "server_http.hpp"


namespace http {

    class HttpServer::HttpServerImpl {
    private:

        using SimpleWebServer = SimpleWeb::Server<SimpleWeb::HTTP>;
        using SimpleWebResponse = std::shared_ptr<SimpleWebServer::Response>;
        using SimpleWebRequest = std::shared_ptr<SimpleWebServer::Request>;

    public:


        explicit HttpServerImpl(unsigned short port) : mServer(), mPool(5) {
            mServer.config.port = port;
        }

        void on_rsp(SimpleWebResponse response, SimpleWebRequest request, Router cb) {
            try {
                Request req;
                std::string content;
                req.method = request->method;
                req.path = request->path;
                req.query = request->query_string;
                req.content = request->content.string();
                if (request->path_match.empty()) {
                    req.match = "";
                } else {
                    req.match = request->path_match[1].str();
                }
                response->write(cb(req));
            }
            catch (const std::exception &e) {
                *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n"
                          << e.what();
            }

        }

        void set_router(const std::string &path, Router cb) {
            auto f = [this, cb](SimpleWebResponse response, SimpleWebRequest request) {
                mPool.enqueue(&HttpServerImpl::on_rsp, this, response, request, cb);
            };

            if (path.empty()) {
                mServer.default_resource["GET"] = f;
                mServer.default_resource["POST"] = f;
            } else {
                auto path2 = "^" + path + "(.*)$";
                mServer.resource[path2]["GET"] = f;
                mServer.resource[path2]["POST"] = f;
            }
        }

        void start(bool use_thread_join) {
            std::thread server_thread([this]() {
                mServer.start([](unsigned short port) {
                    std::cout << "HttpServer listening " << port << std::endl;
                });
                std::cout << "http thread over" << std::endl;
            });
            if (use_thread_join) {
                server_thread.join();
            } else {
                server_thread.detach();
            }
        }

        void stop() {
            mServer.stop();
        }

    private:
        SimpleWebServer mServer;
        ThreadPool mPool;
    };


    HttpServer::HttpServer(unsigned short port) : pImpl(ShareUtils::make_unique<HttpServerImpl>(port)) {

    }

    void HttpServer::set_router(const std::string &path, Router cb) {
        pImpl->set_router(path, std::move(cb));
    }

    void HttpServer::start(bool use_thread_join) {
        pImpl->start(use_thread_join);
    }

    void HttpServer::stop() {
        pImpl->stop();
    }

    HttpServer::~HttpServer() = default;
}