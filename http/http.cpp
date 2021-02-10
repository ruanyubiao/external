//
// Created by ryb on 2021/2/8.
//

#include "http.h"
#include "client_http.hpp"
#include "StringUtils.h"

using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;
using HttpHead = SimpleWeb::CaseInsensitiveMultimap;

std::pair<std::string, std::string> Http::parseUrl(const std::string &url) {
    std::pair<std::string, std::string> ret = std::make_pair("", "");
    auto v = StringUtils::regex_match(url, "^(https?)://(.*?)(/(.*))?");
    if (!v.empty()) {
        ret.first = v[2];
        ret.second = v[4];
    }
    return ret;
}

std::future<std::pair<bool, std::string>> Http::send(const std::string &url, const std::string &data, bool isGet) {
    auto fut = std::async(std::launch::async, &Http::send_sync, url, data, isGet);
    return fut;
}

std::pair<bool, std::string> Http::send_sync(const std::string &url, const std::string &data, bool isGet) {
    std::pair<bool, std::string> ret = std::make_pair(false, "");
    if (url.empty()) {
        return ret;
    }
    auto urldict = parseUrl(url);
    HttpClient client(urldict.first);
    client.config.timeout = 10;
    client.config.timeout_connect = 10;
    try {
        HttpHead head = {
                {"User-Agent",      "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.150 Safari/537.36 Edg/88.0.705.63"},
                {"Content-Type",    "text/html;charset=utf-8"},
                {"Accept-Encoding", "gzip, deflate, br"},
                {"Accept",          "*/*"},
                {"Accept-Encoding", "gzip, deflate, br"},
                {"Connection",      "keep-alive"},
        };
        auto rsp = client.request(isGet ? "GET" : "POST", urldict.second, data, head);
        if (rsp->status_code == "200 OK") {
            ret.first = true;
            ret.second = rsp->content.string();
        } else {
            ret.first = false;
            ret.second = rsp->status_code;
        }

        return ret;
    }
    catch (const SimpleWeb::system_error &e) {
        std::cout << "Client request error: " << e.what() << std::endl;
    }
    return ret;
}