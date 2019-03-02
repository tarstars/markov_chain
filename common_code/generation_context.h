#pragma once
#include "poly_hash.h"

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
        SequenceData(size_t contextLength);
        size_t seqLen;
        PolyHash polyHash;
        friend class MarkovSampler;
        friend class MarkovSampler;
    };

    int contextLength;
    std::vector<SequenceData> seqs;
    friend class MarkovSampler;
};
