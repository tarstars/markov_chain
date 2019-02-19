#include "markov_automaton.h"

#include <boost/tokenizer.hpp>

#include <iostream>
#include <fstream>

MarkovAutomaton::MarkovAutomaton(size_t contextSize): contextSize(contextSize)
{

}

void MarkovAutomaton::UpdateFromString(const std::string& text) {
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    tokenizer tok{text};
    TokenIdProcessor idProcessor(this);
    for (tokenizer::iterator itToken = tok.begin(); itToken != tok.end(); ++itToken) {
        size_t tokenId;
        const auto itId = word2id.find(*itToken);
        if (itId == word2id.end()) {
            tokenId = word2id.size();
            word2id[*itToken] = tokenId;
        } else {
            tokenId = itId->second;
        }
        idProcessor.processTokenId(tokenId);
    }
}

MarkovAutomaton::TokenIdProcessor::TokenIdProcessor(MarkovAutomaton *automaton): automaton(automaton),
    currentPolyHash(0)
{

}

void MarkovAutomaton::TokenIdProcessor::processTokenId(size_t tokenId) {
    inProgress.push(tokenId);
    currentPolyHash = (currentPolyHash * MULT + tokenId) % MODULO;
    if (inProgress.size() < automaton->contextSize) {
        lastDigit = (lastDigit * MULT) % MODULO;
    } else {
        size_t idToRemove = inProgress.front();
        inProgress.pop();
        ++(automaton->matrix[currentPolyHash][tokenId]);
        currentPolyHash = (currentPolyHash + MODULO - (idToRemove * lastDigit) % MODULO ) % MODULO;
    }
}

void MarkovAutomaton::SaveIndex(const std::string& flnm) {
    std::ofstream dest(flnm);
    dest << word2id.size();
    for (const auto& word_id: word2id) {
        dest << word_id.first << " " << word_id.second << std::endl;
    }
}

void MarkovAutomaton::SaveMatrix(const std::string& flnm) {
    std::ofstream dest(flnm);

    dest << matrix.size() << std::endl;
    for (const auto& word2hist: matrix) {
        dest << word2hist.first << std::endl;
        for (const auto& id_freq: word2hist.second) {
            dest << "\t" << id_freq.first << " " << id_freq.second << std::endl;
        }
    }
}
