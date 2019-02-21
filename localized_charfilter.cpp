#include "localized_charfilter.h"

CharToRemove::CharToRemove(): loc("ru_RU.utf8") {

}

bool CharToRemove::operator()(wchar_t c) const {
    return !std::isalpha(c, loc) && c != L' ' && c != L'\t' && c!= '\n';
}

CharToRemove& CharToRemove::getInst() {
    static CharToRemove oneObject;
    return oneObject;
}
