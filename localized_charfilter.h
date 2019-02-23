#ifndef LOCALIZEDCHARFILTER_H
#define LOCALIZEDCHARFILTER_H

#include <locale>
#include <string>

class CharToRemove {
public:
    bool operator()(wchar_t c) const;
    static CharToRemove& getInst();
    std::wstring tolower_locale(std::wstring s) const;
private:
    CharToRemove();
    std::locale loc;
};


#endif // LOCALIZEDCHARFILTER_H
