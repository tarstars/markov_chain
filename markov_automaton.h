#ifndef MARKOV_AUTOMATON_H
#define MARKOV_AUTOMATON_H

#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

class MarkovAutomaton
{
public:
    MarkovAutomaton(size_t constextSize);
    void UpdateFromString(const std::string& text);
    void SaveIndex(const std::string& flnm);
    void SaveMatrix(const std::string& flnm);
private:
    struct TokenIdProcessor {
        const size_t MODULO = 1000003;
        const size_t MULT = 42;

        TokenIdProcessor(MarkovAutomaton* automaton);
        MarkovAutomaton* automaton;
        void processTokenId(size_t tokenId);
        std::queue<size_t> inProgress;
        size_t currentPolyHash;
        size_t lastDigit;
    };

    size_t contextSize;
    std::unordered_map<std::string, std::size_t> word2id;
    std::unordered_map<std::size_t, std::unordered_map<std::size_t, std::size_t>> matrix;
};

#endif // MARKOV_AUTOMATON_H
