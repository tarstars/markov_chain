#ifndef POLY_HASH_H
#define POLY_HASH_H

#include <queue>

class PolyHash
{
public:
    PolyHash(size_t contextSize);
    void push(size_t id);
    bool ripe() const;
    size_t getContextId() const;
    size_t getContextSize() const;
private:
    size_t contextSize;
    std::queue<size_t> inProgress;

    size_t currentPolyHash;
    size_t lastDigit;

    static const size_t MODULO;
    static const size_t MULT;
};

#endif // POLY_HASH_H
