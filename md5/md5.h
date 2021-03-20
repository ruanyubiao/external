#ifndef __EXTERNAL_MD5_H__
#define __EXTERNAL_MD5_H__

#include <string>

namespace md5 {
    //std::string random_string();

    std::string md5(const std::string &input);

    std::string md5(const void *buffer, size_t size);

    std::string md5_file(const std::string &filename);

};


#endif //__EXTERNAL_MD5_H__
