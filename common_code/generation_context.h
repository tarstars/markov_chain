#ifndef GENERATION_CONTEXT_H
#define GENERATION_CONTEXT_H

#include <iostream>
#include <vector>

class GenerationContext
{
public:
    static GenerationContext fromStream(std::istream&);
private:
    GenerationContext();

    class SequenceData {
    public:
        static SequenceData fromStream(std::istream &);
    private:
        size_t seqLen;
        size_t contextId;
    };

    int contextLength;
    std::vector<SequenceData> seqs;
};

#endif // GENERATION_CONTEXT_H
