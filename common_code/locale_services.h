#pragma once

#include <locale>
#include <string>

class LocaleServices {
public:
    bool operator()(wchar_t c) const; // what characters to remove
    static LocaleServices& getInst();
    std::wstring tolower_locale(std::wstring s) const;
private:
    LocaleServices();
    std::locale loc;
};
