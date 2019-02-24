#include "markov_sampler.h"

MarkovSampler::MarkovSampler() {

}

MarkovSampler MarkovSampler::fromStream(std::istream& is) {
    MarkovSampler result;
    is >> result.contextLength;
    int n;
    is >> n;
    if (!is) {
        throw std::runtime_error("stream error during reading of Markov sampler");
    }
    if (n < 0) {
        throw std::runtime_error("negative records number during reading of the Markov sampler");
    }
    size_t unsignedN = n;
    for (size_t meter = 0; meter < unsignedN; ++meter) {
        size_t contextId;
        if (!(is >> contextId)) {
            throw std::runtime_error("stream error during reading of contextId in the Markov sampler");
        }
        auto discreteDistribution = DiscreteDistribution::createFromStream(is);
        result.transitions[contextId] = discreteDistribution;
    }
    return result;
}
