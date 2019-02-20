#ifndef LOCALIZEDCHARFILTER_H
#define LOCALIZEDCHARFILTER_H

#include <locale>

class CharToRemove {
public:
    bool operator()(char c) const;
    static CharToRemove& getInst();
private:
    CharToRemove(): loc("ru_RU.utf8"){}
    std::locale loc;
};


#endif // LOCALIZEDCHARFILTER_H
