#include "generation_context.h"

GenerationContext::GenerationContext()
{

}

GenerationContext GenerationContext::fromStream(std::istream &is) {
    GenerationContext result;
    int contextLength;
    if (!(is >> contextLength)) {
        throw std::runtime_error("stream error during the load of records number in generation context");
    }
    if (contextLength < 0) {
        throw std::runtime_error("records number < 0 in generation context");
    }
    size_t unsignedContextLength = contextLength;
    result.seqs.reserve(contextLength);
    for (size_t meter = 0; meter < unsignedContextLength; ++meter) {
        result.seqs.emplace_back(SequenceData::fromStream(is));
    }

    return result;
}

GenerationContext::SequenceData
GenerationContext::SequenceData::fromStream(std::istream &is) {
    SequenceData result;
    if (!(is >> result.seqLen)) {
        throw std::runtime_error("stream error during load of sequence data");
    }
    return result;
}
