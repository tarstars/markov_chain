#ifndef LOCALIZEDCHARFILTER_H
#define LOCALIZEDCHARFILTER_H

#include <locale>

class CharToRemove {
public:
    bool operator()(wchar_t c) const;
    static CharToRemove& getInst();
private:
    CharToRemove();
    std::locale loc;
};


#endif // LOCALIZEDCHARFILTER_H
