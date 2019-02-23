#include "markov_automaton.h"
#include "localized_charfilter.h"

#include <boost/filesystem.hpp>

#include <array>
#include <clocale>
#include <codecvt>
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
    std::ofstream debug("debug.txt");
    std::string curlCmd("curl ");
    int n;
    if (!(streamN >> n) || n < 1) {
        throw std::runtime_error("wrong number format");
    }
    if (!source) {
        throw std::runtime_error("can't open file <" + uriFlnm + ">");
    }
    // std::locale loc("ru_RU.utf8");
    // std::cout.imbue(loc);
    // std::setlocale(std::LC_ALL, "ru_RU.utf8");
    MarkovAutomaton mark(static_cast<size_t>(n));
    std::string uri;
    while (std::getline(source, uri)) {
        std::string inStr = exec((curlCmd + uri).c_str());
        debug << inStr;
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring winStr = converter.from_bytes(inStr);
        winStr.erase(std::remove_if(winStr.begin(), winStr.end(), CharToRemove::getInst()), winStr.end());
        mark.UpdateFromString(winStr);
    }
    mark.SaveIndex(argv[3]);
    mark.SaveMatrix(argv[4]);
}

void test_rus() {
    std::wstring a(L"Как ныне сбирается вещий 111");

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string b = converter.to_bytes(a);

    // std::cout << b << std::endl;
    std::locale ruLoc("ru_RU.utf8");

    std::wcout << a << std::endl;

    for (size_t ind = 0; ind < a.size(); ++ind) {
        std::wcout << ind << " " << int(a[ind])
                   << " iswalpha = " << std::isalpha(a[ind], ruLoc)
                   << std::endl;
    }
    // wchar_t b = a[0];
    // std::cout << a[0] << " " << std::isalpha(a[0], l) << " "
    //           << std::isalpha(b, l) << std::endl ;
}

int main(int argc, const char **argv)
{
    //  test_rus();     return 0;
    try {
        doMain(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }
    return 0;
}
