#include "locale_services.h"

#include <memory>

LocaleServices::LocaleServices() {

}

bool LocaleServices::operator()(wchar_t c) const {
    static std::wstring nonAlphaExceptions = L" \t\n<>=";
    return !std::isalpha(c, *loc) &&  nonAlphaExceptions.find(c) == std::string::npos;
}

LocaleServices& LocaleServices::getInst() {
    static LocaleServices singleton;
    return singleton;
}

std::wstring LocaleServices::tolower_locale(std::wstring s) const {
    for (size_t ind = 0; ind < s.size(); ++ind) {
        s[ind] = std::tolower(s[ind], *loc);
    }
    return s;
}

void LocaleServices::setLocale(const std::string &localeName) {
    auto tmpLocale = std::make_unique<std::locale>(localeName);
    loc.swap(tmpLocale);
}
