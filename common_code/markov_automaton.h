#ifndef MARKOV_AUTOMATON_H
#define MARKOV_AUTOMATON_H

#include "poly_hash.h"

#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

class MarkovAutomaton
{
public:
    MarkovAutomaton(size_t constextSize);
    void update(const std::wstring& text);
    void SaveIndex(const std::string& flnm);
    void SaveMatrix(const std::string& flnm);
private:
    void processTokenId(size_t id);
    PolyHash polyHash;
    std::unordered_map<std::wstring, std::size_t> word2id;
    std::unordered_map<std::size_t, std::unordered_map<std::size_t, std::size_t>> matrix;
};

#endif // MARKOV_AUTOMATON_H
