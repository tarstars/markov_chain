#ifndef GENERATION_CONTEXT_H
#define GENERATION_CONTEXT_H

#include <iostream>
#include <vector>

class MarkovSampler;

class GenerationContext
{
public:
    static GenerationContext fromStream(std::istream&, const MarkovSampler& );
private:
    GenerationContext();

    class SequenceData {
    public:
        static SequenceData fromStream(std::istream &, const MarkovSampler& );
    private:
        size_t seqLen;
        size_t contextId;
    };

    int contextLength;
    std::vector<SequenceData> seqs;
};

#endif // GENERATION_CONTEXT_H
