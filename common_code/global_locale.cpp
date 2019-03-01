#include "global_locale.h"

#include <memory>

GlobalLocale::GlobalLocale() {

}

GlobalLocale& GlobalLocale::getInstance() {
    static GlobalLocale singleton;
    return singleton;
}

void GlobalLocale::setLocale(const std::string &localeName) {
    auto tmpLocale = std::make_shared<std::locale>(localeName);
    getInstance().loc.swap(tmpLocale);
}

const std::shared_ptr<std::locale>& GlobalLocale::getLocale() {
    return getInstance().loc;
}
