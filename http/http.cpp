#include "http.h"

#ifndef USE_STANDALONE_ASIO
#define USE_STANDALONE_ASIO 1
#endif

#include <thread>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include "ThreadPool.h"
#include "server_http.hpp"


namespace http {

    using SimpleWebServer = SimpleWeb::Server<SimpleWeb::HTTP>;
    using SimpleWebResponse = std::shared_ptr<SimpleWebServer::Response>;
    using SimpleWebRequest = std::shared_ptr<SimpleWebServer::Request>;


    class FileServer {
    public:
        static void read_and_send(const SimpleWebResponse &response, const std::shared_ptr<std::ifstream> &ifs) {
            constexpr std::size_t SIZE = 128 * 1024;
            // Read and send 128 KB at a time
            static std::vector<char> buffer(SIZE); // Safe when server is running on one thread
            std::streamsize read_length = ifs->read(&buffer[0], SIZE).gcount();
            if (read_length <= 0) {
                return;
            }
            response->write(&buffer[0], read_length);
            if (read_length == SIZE) {
                response->send([response, ifs](const SimpleWeb::error_code &ec) {
                    if (!ec)
                        read_and_send(response, ifs);
                    else
                        std::cerr << "Connection interrupted" << std::endl;
                });
            }
        }
    };

    Request getRequest(const SimpleWebRequest &request) {
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
        return req;
    }

    class HttpServer::HttpServerImpl {
    public:

        explicit HttpServerImpl(unsigned short port) : mServer(), mPool(5) {
            mServer.config.port = port;
        }

        void on_rsp(const SimpleWebResponse &response, const SimpleWebRequest &request, const Router &cb) {
            try {
                auto req = getRequest(request);
                response->write(cb(req));
            }
            catch (const std::exception &e) {
                *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n"
                          << e.what();
            }
        }

        void on_error(const SimpleWebRequest &request, const SimpleWeb::error_code &ec,
                      const std::function<void(const Request &)> &cb) {
            // Handle errors here
            // Note that connection timeouts will also call this handle with ec set to SimpleWeb::errc::operation_canceled
        }

        void set_router(const Router &cb, const std::string &path, const std::string &method) {
            auto f = [this, cb](const SimpleWebResponse &response, const SimpleWebRequest &request) {
                this->mPool.enqueue(&HttpServerImpl::on_rsp, this, response, request, cb);
            };

            if (path.empty()) {
                mServer.default_resource[method] = f;
            } else {
                auto path2 = "^" + path + "(.*)$";
                mServer.resource[path2][method] = f;
            }
        }

        void set_error(const std::function<void(const Request &)> &cb) {
            mServer.on_error = [this, cb](const SimpleWebRequest &request, const SimpleWeb::error_code &ec) {
                this->mPool.enqueue(&HttpServerImpl::on_error, this, request, ec, cb);
            };
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


    HttpServer::HttpServer(unsigned short port) : pImpl(std::make_unique<HttpServerImpl>(port)) {

    }

    void HttpServer::set_router(const Router &cb, const std::string &path, const std::string &method) {
        pImpl->set_router(cb, path, method);
    }

    void HttpServer::start(bool use_thread_join) {
        pImpl->start(use_thread_join);
    }

    void HttpServer::stop() {
        pImpl->stop();
    }

    void HttpServer::set_error(const std::function<void(const Request &)> &cb) {
        pImpl->set_error(cb);
    }

    HttpServer::~HttpServer() = default;
}