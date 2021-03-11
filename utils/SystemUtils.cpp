#include <cstdio>
#include "SystemUtils.h"

namespace sys {
    std::string system(const std::string &cmd) {
        std::string ret;
        char buf[1024] = {0};
        FILE *fp = popen(cmd.c_str(), "r");
        if (fp == nullptr) {
            printf("popen error!\n");
            return "";
        }

        while (fgets(buf, sizeof(buf), fp)) {
            ret += buf;
        }
        return ret;
    }

    std::string get_host_ip() {
        std::string ip;
#ifdef __linux
        ip = system("hostname -I | awk '{print $1}'");
#endif
        return ip;
    }
}