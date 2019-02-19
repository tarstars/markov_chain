#include "markov_automaton.h"

#include <boost/filesystem.hpp>

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <string>
#include <array>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::stringstream result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result << buffer.data();
    }
    return result.str();
}

void checkParameters(int argc, const char **argv) {
    if (argc != 5) {
        std::cerr << "usage: " << boost::filesystem::basename(argv[0])
                  << " <file with urls> <context len> <dict file> <markov matrix file>" << std::endl;
        throw std::runtime_error("");
    }
}

void doMain(int argc, const char **argv) {
    checkParameters(argc, argv);
    std::string uriFlnm(argv[1]);
    std::stringstream streamN(argv[2]);
    std::ifstream source(uriFlnm);
    std::string curlCmd("curl ");
    int n;
    if (!(streamN >> n) || n < 1) {
        throw std::runtime_error("wrong number format");
    }
    if (!source) {
        throw std::runtime_error("can't open file <" + uriFlnm + ">");
    }
    MarkovAutomaton mark(static_cast<size_t>(n));
    std::string uri;
    while (std::getline(source, uri)) {
        auto inStr = exec((curlCmd + uri).c_str());
        mark.UpdateFromString(inStr);
    }
    mark.SaveIndex(argv[3]);
    mark.SaveMatrix(argv[4]);
}

int main(int argc, const char **argv)
{
    try {
        doMain(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }
    return 0;
}
