#include <codecvt>
#include <iostream>
#include <fstream>
#include <locale>

using namespace std;

void testReadStringFromFile() {
    // std::setlocale(LC_ALL, "ru_RU.utf8");
    std::string s1 = "t11й11";
    std::cout << "ordinary string " << s1 << std::endl;
    for (size_t ind = 0; ind < s1.size(); ++ind) {
        std::cout << s1[ind] << " "
                  << std::boolalpha << (bool)std::isalpha(static_cast<unsigned char>(s1[ind])) << std::endl;
    }
    std::cout << std::endl;
    std::ifstream source("utf8.txt");
    std::string s2;
    if (!(std::getline(source, s2))) {
        std::cerr << "file read error" << std::endl;
        return;
    }
    std::cout << "from file: s2 = " << s2 << std::endl;
    for (size_t ind = 0; ind < s2.size(); ++ind) {
        std::cout << s2[ind] << " "
                  << std::boolalpha << (bool)std::isalpha(static_cast<unsigned char>(s2[ind])) << std::endl;
    }
    std::cout << std::endl;

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring ws = converter.from_bytes(s2);
    std::wcout << "ws = " << ws << std::endl;
    for (size_t ind = 0; ind < ws.size(); ++ind) {
        std::wcout << ws[ind] << " "
                  << std::boolalpha << (bool)std::isalpha(ws[ind]) << std::endl;
    }
    std::cout << std::endl;

    std::locale loc("en_US.utf8");
    std::wstring ws2 = converter.from_bytes(s2);
    std::wcout << "ws2 = " << ws << std::endl;
    for (size_t ind = 0; ind < ws2.size(); ++ind) {
        std::wcout << ws2[ind] << " "
                  << std::boolalpha << (bool)std::isalpha(ws2[ind], loc) << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    // std::string s = "а б в<>";
    // std::cout << "s = " << s << std::endl;
    testReadStringFromFile();
    return 0;
}
