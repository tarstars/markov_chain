#include "../common_code/automaton_updater.h"
#include "../common_code/markov_automaton.h"
#include "../common_code/util.h"
#include "../common_code/global_locale.h"

#include <algorithm>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <sstream>

void doMain(int argc, const char **argv) {
    auto cmdParams = getMarkovParameters(argc, argv);
    std::string uriFlnm(cmdParams["uri_flnm"]);
    std::stringstream streamN(cmdParams["context_len"]);
    std::string modelFilePrefix = cmdParams["model_file_prefix"];
    std::string modelIndexFileName = modelFilePrefix + ".idx";
    std::string modelMatrixFileName = modelFilePrefix + ".mtx";

    GlobalLocale::setLocale(cmdParams["locale"]);

    std::ifstream source(uriFlnm);
    int n;
    if (!(streamN >> n) || n < 1) {
        throw std::runtime_error("wrong number format");
    }
    if (!source) {
        throw std::runtime_error("can't open file <" + uriFlnm + ">");
    }
    std::string uri;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    MarkovAutomaton mark(static_cast<size_t>(n));
    AutomatonUpdater<MarkovAutomaton, decltype(converter)>
            automatonUpdater(&mark, converter);
    while (std::getline(source, uri)) {
        callWordProcessor("curl", uri, automatonUpdater);
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
