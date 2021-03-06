#ifndef MARKOV_SAMPLER_H
#define MARKOV_SAMPLER_H

#include "discrete_distribution.h"

#include <istream>
#include <unordered_map>

class GenerationContext;
class SequenceData;

class MarkovSampler {
public:
    MarkovSampler();
    static MarkovSampler loadSampler(const std::string& modelMatrixFileName,
                                     const std::string& modelIndexFileName);
    size_t getContextLength() const;
    size_t getIdByToken(const std::string&) const;
    void generateFromContext(const GenerationContext& generationContext);
    void generateFromSequenceData(const GenerationContext::SequenceData& sd);
private:
    size_t contextLength;
    std::unordered_map<size_t, DiscreteDistribution> transitions;
    std::unordered_map<size_t, std::string> id2token;
    std::unordered_map<std::string, size_t> token2id;
};

#endif // MARKOV_SAMPLER_H
