#ifndef __FILE_UTILS_H__
#define __FILE_UTILS_H__

#include <vector>
#include <memory>
#include <string>

class FileUtils {
    static std::shared_ptr<std::vector<uint8_t>> get_file_bin(const std::string &filename);

    static std::shared_ptr<std::string> get_file_str(const std::string &filename);

    static bool write_file_bin(const std::string &filename, const char *content, int size, bool newfile = true);

    static bool exist(const std::string &name);

};


#endif//__FILE_UTILS_H__
