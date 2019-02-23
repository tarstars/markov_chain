#include "markov_automaton.h"
#include "util.h"

#include "localized_charfilter.h"

#include <algorithm>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <sstream>

void doMain(int argc, const char **argv) {
    auto cmdParams = getParameters(argc, argv);
    std::string uriFlnm(cmdParams["uri_flnm"]);
    std::stringstream streamN(cmdParams["context_len"]);
    std::string modelFilePrefix = cmdParams["model_file_prefix"];
    std::string modelIndexFileName = modelFilePrefix + ".idx";
    std::string modelMatrixFileName = modelFilePrefix + ".mtx";
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
        std::string inStr = exec((curlCmd + uri).c_str());
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring winStr = converter.from_bytes(inStr);
        winStr.erase(std::remove_if(winStr.begin(), winStr.end(), CharToRemove::getInst()), winStr.end());
        mark.UpdateFromString(winStr);
    }
    mark.SaveIndex(modelIndexFileName);
    mark.SaveMatrix(modelMatrixFileName);
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
