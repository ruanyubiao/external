#include <fstream>
#include <sstream>

#include "FileUtils.h"

std::shared_ptr<std::vector<uint8_t>> FileUtils::get_file_bin(const std::string &filename) {
    //seekg->read 方式

    std::shared_ptr<std::vector<uint8_t>> ret;
    std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
    if (in.good()) {
        in.seekg(0, std::ios::end);
        auto length = in.tellg();
        in.seekg(0, std::ios::beg);

        ret = std::make_shared<std::vector<uint8_t>>(length);
        in.read((char *) ret->data(), length);
    }
    in.close();
    return ret;
}

std::shared_ptr<std::string> FileUtils::get_file_str(const std::string &filename) {
    std::ifstream in(filename.c_str());
    if (in.good()) {
        std::stringstream buffer;
        buffer << in.rdbuf();
        return std::make_shared<std::string>(buffer.str());
    }

    return nullptr;
}

bool FileUtils::write_file_bin(const std::string &filename, const char *content, int size, bool newfile) {
    bool state = false;
    auto mode = std::ios::out | std::ios::binary | (newfile ? std::ios::ate : std::ios::app);

    std::ofstream out(filename.c_str(), mode);
    if (out.good()) {
        out.write(content, size);
        state = true;
    }
    out.close();
    return state;
}

bool FileUtils::exist(const std::string &name) {
    std::ifstream in(name);
    bool state = in.good();
    in.close();
    return state;
}
/*
int write_file_bin_c(const char* filename, const char* content, int size, bool newfile)
{
    FILE* fp = fopen(filename, newfile ? "wb" : "ab+");
    if (fp == NULL)
    {
        printf("Cannot open file %s !", filename);
        return -1;
    }
    fwrite(content, size, 1, fp);
    fclose(fp);
    return 0;
}
*/