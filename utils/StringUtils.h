#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <string>
#include <vector>


namespace StringUtils {
    //template <typename... Args>
    //std::string format2(const std::string& format, Args... args);

    std::string format(const char *format, ...);

    std::vector<std::string> split(const std::string &s, const std::string &delimiters = " ");

    std::vector<std::string> split_regex(const std::string &s, const std::string &delimiters = " ");

    std::vector<std::string> regex_match(const std::string &s, const std::string &r);

    std::string &replace_one(std::string &str, const std::string &old_value, const std::string &new_value);

    std::string &replace_all(std::string &str, const std::string &old_value, const std::string &new_value);

}


#endif //__STRING_UTILS_H__