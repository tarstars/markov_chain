#include "discrete_distribution.h"
#include "random_singleton.h"

#include <algorithm>
#include <limits>

DiscreteDistribution::DiscreteDistribution() {

}

DiscreteDistribution DiscreteDistribution::createFromStream(std::istream &is) {
    int n;
    is >> n;
    if (!is) {
        throw std::runtime_error("stream error reading DiscreteDistribution");
    }
    if (n < 0) {
        throw std::runtime_error("negative amount of records reading DiscreteDistribution");
    }
    DiscreteDistribution result;
    size_t unsizedN(n);
    result.cumulativeDensity.reserve(n);
    result.tokenIds.reserve(n);
    double freqSum = 0;
    for (size_t meter = 0; meter < unsizedN; ++meter) {
        size_t id, freq;
        if (!(is >> id >> freq)) {
            throw std::runtime_error("stream error during reading frequencies of DiscreteDistribution");
        }
        freqSum += freq;
        result.tokenIds.emplace_back(id);
        result.cumulativeDensity.emplace_back(freqSum);
    }

    if (freqSum < 1.0) {
        throw std::runtime_error("total weight < 1 during reading frequencies of DiscreteDistribution");
    }

    for (size_t meter = 0; meter < unsizedN; ++meter) {
        result.cumulativeDensity[meter] /= freqSum;
    }

    return result;
}

size_t DiscreteDistribution::drawRandomId() const {
    double x = RandomSingleton::rand() * (1-std::numeric_limits<double>::epsilon());
    size_t ind = std::lower_bound(cumulativeDensity.begin(),
                                  cumulativeDensity.end(),
                                  x) - cumulativeDensity.begin();
    return tokenIds[ind];
}
