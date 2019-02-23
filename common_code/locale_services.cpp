#include "locale_services.h"

LocaleServices::LocaleServices(): loc("ru_RU.utf8") {

}

bool LocaleServices::operator()(wchar_t c) const {
    static std::wstring nonAlphaExceptions = L" \t\n<>=";
    return !std::isalpha(c, loc) &&  nonAlphaExceptions.find(c) == std::string::npos;
}

LocaleServices& LocaleServices::getInst() {
    static LocaleServices singleton;
    return singleton;
}

std::wstring LocaleServices::tolower_locale(std::wstring s) const {
    for (size_t ind = 0; ind < s.size(); ++ind) {
        s[ind] = std::tolower(s[ind], loc);
    }
    return s;
}
