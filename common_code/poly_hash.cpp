#include "poly_hash.h"

const size_t PolyHash::MODULO = 1000003;
const size_t PolyHash::MULT = 42;

PolyHash::PolyHash(size_t contextSize) : contextSize(contextSize),
    currentPolyHash(0), lastDigit(1)
{

}

void PolyHash::push(size_t id) {
    inProgress.push(id);
    size_t nextPolyHash = (currentPolyHash * MULT + id) % MODULO;
    if (inProgress.size() <= contextSize) {
        lastDigit = (lastDigit * MULT) % MODULO;
    } else {
        size_t idToRemove = inProgress.front();
        inProgress.pop();
        nextPolyHash = (nextPolyHash + (MODULO - (idToRemove * lastDigit) % MODULO)) % MODULO;
    }
    currentPolyHash = nextPolyHash;
}

bool PolyHash::ripe() const {
    return inProgress.size() >= contextSize;
}

size_t PolyHash::getContextId() const {
    return currentPolyHash;
}

size_t PolyHash::getContextSize() const {
    return contextSize;
}
