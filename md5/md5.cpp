#include "md5.h"
#include "include/md5.hpp"
#include <fstream>

using namespace websocketpp::md5;

namespace md5 {
/*    std::string random_string() {
        std::random_device rd;

        auto timePoint = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now());
        uint32_t timestamp = (uint32_t) timePoint.time_since_epoch().count();

        return md5_hash_hex(std::to_string(timestamp + rd()));
    }*/


    std::string hash_to_hex(const char *hash, size_t size) {
        std::string hex;
        for (size_t i = 0; i < size; i++) {
            hex.push_back(hexval[((hash[i] >> 4) & 0xF)]);
            hex.push_back(hexval[(hash[i]) & 0x0F]);
        }
        return hex;
    }

    std::string md5(const std::string &input) {
        return md5_hash_hex(input);
    }

    std::string md5(const void *buffer, size_t size) {
        char digest[16];

        md5_state_t state;
        md5_init(&state);
        md5_append(&state, (md5_byte_t const *) buffer, size);
        md5_finish(&state, (md5_byte_t *) digest);

        return hash_to_hex(digest, 16);
    }

    std::string md5_file(const std::string &filename) {
        std::ifstream in(filename.c_str(), std::ios::binary);
        if (!in) {
            return "";
        }

        md5_state_t state;
        md5_init(&state);

        std::streamsize length;
        char buffer[4096];
        while (!in.eof()) {
            in.read(buffer, 4096);
            length = in.gcount();
            if (length > 0) {
                md5_append(&state, (md5_byte_t const *) buffer, length);
            }
        }
        in.close();

        char digest[16];
        md5_finish(&state, (md5_byte_t *) digest);

        return hash_to_hex(digest, 16);
    }


}