#include <string>

#ifndef __TESTEXTERNAL_OS_H__
#define __TESTEXTERNAL_OS_H__

namespace sys {
    std::string system(const std::string &cmd);

    std::string get_host_ip();

}


#endif //__TESTEXTERNAL_OS_H__
