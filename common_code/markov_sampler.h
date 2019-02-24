#ifndef MARKOV_SAMPLER_H
#define MARKOV_SAMPLER_H

#include "discrete_distribution.h"

#include <istream>
#include <unordered_map>

class MarkovSampler {
public:
    MarkovSampler();
private:
    static MarkovSampler fromStream(std::istream&);
    size_t contextLength;
    std::unordered_map<size_t, DiscreteDistribution> transitions;
};

#endif // MARKOV_SAMPLER_H
