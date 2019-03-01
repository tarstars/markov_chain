#include "../common_code/markov_automaton.h"
#include "../common_code/util.h"

#include "../common_code/global_locale.h"

#include <algorithm>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <sstream>

// TODO: fix triple memory usage
// TODO: fix encoding problem
// TODO: fix dirty #include
// TODO: fix inoptimality in update of word2id
// TODO: unify format of exception messages, incorporate file, line, class and method in
//       the message
// TODO: write unittests for this project
// TODO: dehardcode locale
// TODO: place random seed in the configuration file

class LettersToIgnore {
public:
    bool operator()(wchar_t c) const {
        static std::wstring nonAlphaExceptions = L" \t\n<>=";
        return !std::isalpha(c, *loc) &&  nonAlphaExceptions.find(c) == std::string::npos;
    }
    LettersToIgnore(): loc(GlobalLocale::getLocale())  {}
private:
    std::shared_ptr<const std::locale> loc;
};

void doMain(int argc, const char **argv) {
    auto cmdParams = getMarkovParameters(argc, argv);
    std::string uriFlnm(cmdParams["uri_flnm"]);
    std::stringstream streamN(cmdParams["context_len"]);
    std::string modelFilePrefix = cmdParams["model_file_prefix"];
    std::string modelIndexFileName = modelFilePrefix + ".idx";
    std::string modelMatrixFileName = modelFilePrefix + ".mtx";

    GlobalLocale::setLocale(cmdParams["locale"]);

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
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring winStr;
        {
            std::string inStr = exec((curlCmd + uri).c_str());
            winStr = converter.from_bytes(inStr);
        }
        winStr.erase(std::remove_if(winStr.begin(), winStr.end(), LettersToIgnore()), winStr.end());
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
    } catch (const std::bad_alloc& err) {
        std::cerr << "memory allocation error" << std::endl;
        return 2;
    }
    return 0;
}
