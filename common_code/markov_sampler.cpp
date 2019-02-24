#include "markov_sampler.h"

#include <fstream>

MarkovSampler::MarkovSampler() {

}

MarkovSampler MarkovSampler::loadSampler(const std::string& modelMatrixFileName,
                                         const std::string& modelIndexFileName) {
    MarkovSampler result;

    // read model matrix
    {
        std::ifstream matrixStream(modelMatrixFileName);
        matrixStream >> result.contextLength;
        int n;
        matrixStream >> n;
        if (!matrixStream) {
            throw std::runtime_error("stream error during reading of Markov sampler");
        }
        if (n < 0) {
            throw std::runtime_error("negative records number during reading of matrix in the Markov sampler");
        }
        size_t unsignedN = n;
        for (size_t meter = 0; meter < unsignedN; ++meter) {
            size_t contextId;
            if (!(matrixStream >> contextId)) {
                throw std::runtime_error("stream error during reading of contextId in the Markov sampler");
            }
            auto discreteDistribution = DiscreteDistribution::createFromStream(matrixStream);
            result.transitions[contextId] = discreteDistribution;
        }
    }

    // read model index
    {
        std::ifstream indexStream(modelIndexFileName);
        int n;
        if (!(indexStream >> n)) {
            throw std::runtime_error("stream error during reading of the index in the Markov sampler");
        }
        if (n < 0) {
            throw std::runtime_error("negative records number during reading of the index in the Markov sampler");
        }

        size_t unsignedN = n;
        for (size_t meter = 0; meter < unsignedN; ++meter) {
            std::string token;
            size_t id;
            indexStream >> token >> id;
            result.id2token[id] = token;
            result.token2id[token] = id;
        }
    }
    return result;
}

size_t MarkovSampler::getContextLength() const {
    return contextLength;
}

size_t MarkovSampler::getIdByToken(const std::string& token) const {
    auto it = token2id.find(token);
    if (it == token2id.end()) {
        throw std::runtime_error(std::string("there is no token <") +
                                 token + "> in model");
    }
    return it->second;
}
