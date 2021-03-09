#include "StringUtils.h"
#include <regex>
#include <memory>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdarg>

using namespace std;

namespace StringUtils {



    //template<typename ... Args>
    //std::string format2(const string& format, Args ... args) {
    //    size_t size = 1 + snprintf(nullptr, 0, format.c_str(), args ...);  // Extra space for \0
    //    unique_ptr<char[]> buffer(new char[size] {0});
    //    snprintf(buffer.get(), size, format.c_str(), args ...);
    //    return string(buffer.get());
    //}

    /*--- This a C++ universal sprintf in the future.
    **  @pitfall: The behavior of vsnprintf between VS2013 and VS2015/2017 is different
    **      VS2013 or Unix-Like System will return -1 when buffer not enough, but VS2015/2017 will return the actural needed length for buffer at this station
    **      The _vsnprintf behavior is compatible API which always return -1 when buffer isn't enough at VS2013/2015/2017
    **      Yes, The vsnprintf is more efficient implemented by MSVC 19.0 or later, AND it's also standard-compliant, see reference: http://www.cplusplus.com/reference/cstdio/vsnprintf/
    */
    std::string format(const char *format, ...) {
        va_list args;
        std::string buffer(512, '\0');

        va_start(args, format);
        int nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
        va_end(args);

        if (nret >= 0) {
            if ((unsigned int) nret < buffer.length()) {
                buffer.resize(nret);
            } else if ((unsigned int) nret > buffer.length()) { // VS2015/2017 or later Visual Studio Version
                buffer.resize(nret);

                va_start(args, format);
                nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
                va_end(args);

                //assert(nret == buffer.length());
            }
            // else equals, do nothing.
        } else { // less or equal VS2013 and Unix System glibc implement.
            do {
                buffer.resize(buffer.length() * 3 / 2);

                va_start(args, format);
                nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
                va_end(args);

            } while (nret < 0);

            buffer.resize(nret);
        }

        return buffer;
    }


    vector<string> split(const string &s, const string &delimiters) {
        vector<string> vec;

        string::size_type lastPos = s.find_first_not_of(delimiters, 0);
        string::size_type pos = s.find_first_of(delimiters, lastPos);
        while (string::npos != pos || string::npos != lastPos) {
            vec.emplace_back(s.substr(lastPos, pos - lastPos));
            lastPos = s.find_first_not_of(delimiters, pos);
            pos = s.find_first_of(delimiters, lastPos);
        }

        return vec;
    }

    vector<string> split_regex(const string &s, const string &delimiters) {
        regex ws_re(delimiters); // whitespace "\\s+"
        vector<string> vec(sregex_token_iterator(s.begin(), s.end(), ws_re, -1), sregex_token_iterator());
        return vec;
    }

    vector<string> regex_match(const string &s, const string &r) {
        vector<string> ret(0);
        std::regex reg(r);
        std::smatch m;
        auto state = std::regex_match(s, m, reg);
        if (state) {
            // m.str(2);
            // m.str(3);
            for (auto &d : m) {
                ret.push_back(d.str());
            }
        }
        return ret;
    }

    string &replace_one(string &str, const string &old_value, const string &new_value) {
        string::size_type pos(0);
        if ((pos = str.find(old_value, pos)) != string::npos)
            str.replace(pos, old_value.length(), new_value);
        return str;
    }

    string &replace_all(string &str, const string &old_value, const string &new_value) {
        string::size_type pos = str.find(old_value), t_size = old_value.size(), r_size = new_value.size();
        while (pos != std::string::npos) {
            str.replace(pos, t_size, new_value);
            pos = str.find(old_value, pos + r_size);
        }
        return str;
    }

    inline std::string &ltrim(std::string &str) {
        auto iter = std::find_if(str.begin(), str.end(), [](const char &ch) {
            return !isspace(ch);
        });
        str.erase(str.begin(), iter);
        return str;
    }

    inline std::string &rtrim(std::string &str) {
        auto iter = std::find_if(str.rbegin(), str.rend(), [](const char &ch) {
            return !isspace(ch);
        });
        str.erase(iter.base(), str.end());

        return str;
    }

    inline std::string &trim(std::string &str) {
        ltrim(rtrim(str));
        return str;
    }


}
