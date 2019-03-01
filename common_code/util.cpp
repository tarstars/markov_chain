#include "global_locale.h"
#include "util.h"

#include <array>
#include <boost/filesystem.hpp>
#include <clocale>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <string>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

void checkMarkovParameters(int argc, const char **argv) {
    if (argc != 4 && argc != 5) {
        std::cerr << "usage: " << boost::filesystem::basename(argv[0])
                  << " <file with urls> <context len> <prefix for dict and index files> [<locale>]" << std::endl;
        throw std::runtime_error("");
    }
}

std::map<std::string, std::string> getMarkovParameters(int argc, const char** argv) {
    checkMarkovParameters(argc, argv);
    std::map<std::string, std::string> result;

    result["uri_flnm"] = argv[1];
    result["context_len"] = argv[2];
    result["model_file_prefix"] = argv[3];
    result["locale"] = "ru_RU.utf8";

    if (5 == argc) {
        result["locale"] = argv[4];
    }

    return result;
}

void checkGeneratorParameters(int argc, const char **argv) {
    if (argc != 3) {
        std::cerr << "usage: " << boost::filesystem::basename(argv[0])
                  << " <prefix for dict and index files> <context file>" << std::endl;
        throw std::runtime_error("");
    }
}

std::map<std::string, std::string> getGeneratorParameters(int argc, const char** argv) {
    checkGeneratorParameters(argc, argv);
    std::map<std::string, std::string> result;

    result["model_file_prefix"] = argv[1];
    result["context_flnm"] = argv[2];

    return result;
}

std::wstring tolower_locale(std::wstring s) {
    const auto& loc = GlobalLocale::getLocale();
    for (size_t ind = 0; ind < s.size(); ++ind) {
        s[ind] = std::tolower(s[ind], *loc);
    }
    return s;
}
