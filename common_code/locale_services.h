#pragma once

#include <locale>
#include <string>
#include <memory>

class LocaleServices {
public:
    bool operator()(wchar_t c) const; // what characters to remove
    static LocaleServices& getInst();
    std::wstring tolower_locale(std::wstring s) const;
    void setLocale(const std::string &localeName);
private:
    LocaleServices();
    std::unique_ptr<std::locale> loc;
};
