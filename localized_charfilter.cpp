#include "localized_charfilter.h"

CharToRemove::CharToRemove(): loc("ru_RU.utf8") {

}

bool CharToRemove::operator()(wchar_t c) const {
    static std::wstring nonAlphaExceptions = L" \t\n<>=";
    return !std::isalpha(c, loc) &&  nonAlphaExceptions.find(c) == std::string::npos;
}

CharToRemove& CharToRemove::getInst() {
    static CharToRemove oneObject;
    return oneObject;
}

std::wstring CharToRemove::tolower_locale(std::wstring s) const {
    for (size_t ind = 0; ind < s.size(); ++ind) {
        s[ind] = std::tolower(s[ind], loc);
    }
    return s;
}
