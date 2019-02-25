#include "generation_context.h"
#include "markov_sampler.h"
#include "poly_hash.h"

GenerationContext::GenerationContext()
{

}

GenerationContext GenerationContext::fromStream(std::istream &is,
                                                const MarkovSampler &markovSampler) {
    GenerationContext result;
    int contextLength;
    if (!(is >> contextLength)) {
        throw std::runtime_error("stream error during the load of records number in generation context");
    }
    if (contextLength < 0) {
        throw std::runtime_error("records number < 0 in generation context");
    }
    size_t unsignedContextLength = contextLength;
    if (unsignedContextLength != markovSampler.getContextLength()) {
        throw std::runtime_error("different context lengths of generation context and model");
    }
    result.seqs.reserve(contextLength);
    int contextsNumber;
    if (!(is >> contextsNumber)) {
        if (contextsNumber < 0) {
            throw std::runtime_error("negative contexts number in GenerationContext::fromStream");
        }
    }
    size_t unsignedContextsNumber = contextsNumber;
    for (size_t meter = 0; meter < unsignedContextsNumber; ++meter) {
        result.seqs.emplace_back(SequenceData::fromStream(is, markovSampler));
    }

    return result;
}

GenerationContext::SequenceData::SequenceData(size_t contextLength): polyHash(contextLength) {

}

GenerationContext::SequenceData
GenerationContext::SequenceData::fromStream(std::istream &is,
                                            const MarkovSampler &markovSampler) {
    SequenceData result(markovSampler.getContextLength());
    if (!(is >> result.seqLen)) {
        throw std::runtime_error("stream error during load of sequence data");
    }
    size_t contextLength = markovSampler.getContextLength();
    PolyHash polyHash(contextLength);
    for (size_t meter = 0; meter < contextLength; ++meter) {
        std::string token;
        if (!(is >> token)) {
            throw std::runtime_error("stream error during read of sequence data");
        }
        polyHash.push(markovSampler.getIdByToken(token));
    }
    if (!polyHash.ripe()) {
        throw std::runtime_error("poly hash is not full in SequenceData::fromStream");
    }
    result.polyHash = polyHash;

    return result;
}
