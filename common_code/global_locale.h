#pragma once

#include <locale>
#include <string>
#include <memory>

class GlobalLocale {
public:
    static void setLocale(const std::string &localeName);
    static const std::shared_ptr<std::locale>& getLocale();
private:
    GlobalLocale();
    static GlobalLocale& getInstance();
    std::shared_ptr<std::locale> loc;
};
