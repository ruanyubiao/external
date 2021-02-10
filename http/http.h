//
// Created by ryb on 2021/2/8.
//

#ifndef __EXTERNAL_HTTP_H__
#define __EXTERNAL_HTTP_H__

#include <utility>
#include <future>
#include <string>

class Http {
private:
    static std::pair<std::string, std::string> parseUrl(const std::string &url);

public:

    static std::future<std::pair<bool, std::string>> send(const std::string &url, const std::string &data, bool isGet);

    static std::pair<bool, std::string> send_sync(const std::string &url, const std::string &data, bool isGet);
};


#endif //__EXTERNAL_HTTP_H__
