#ifndef __EXTERNAL_HTTPSERVER_H__
#define __EXTERNAL_HTTPSERVER_H__


#include <memory>
#include <string>
#include <functional>

namespace http {
    class Request {
    public:
        std::string method;
        std::string path;
        std::string match;
        std::string query;
        std::string content;
    };

    /*
     *
        http::HttpServer server(8080);
        server.set_router("", [](const http::Request &req) {
            return "default";
        });

        server.set_router("/path1", [](const http::Request &req) {
            return "match path  ^/path1(.*)$";
        });

        server.set_router("/path2/", [](const http::Request &req) {
            return "match path  ^/path2/(.*)$";
        });
     *
     */
    class HttpServer {
    private:
        class HttpServerImpl;

    public:
        using Router = std::function<std::string(const Request &)>;
    public:

        explicit HttpServer(unsigned short port = 8080);

        void set_router(const std::string &path, Router cb);

        void start(bool use_thread_join = true);

        void stop();

        ~HttpServer();

    private:
        std::unique_ptr<HttpServerImpl> pImpl;
    };

}


#endif //__EXTERNAL_HTTPSERVER_H__
