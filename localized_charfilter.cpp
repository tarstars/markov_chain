#include "localized_charfilter.h"

bool CharToRemove::operator()(char c) const {
    return !std::isalpha(c, loc) && c != ' ' && c != '\t';
}

CharToRemove& CharToRemove::getInst() {
    static CharToRemove oneObject;
    return oneObject;
}
