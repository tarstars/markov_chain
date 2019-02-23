#include "markov_automaton.h"
#include "localized_charfilter.h"

#include <boost/tokenizer.hpp>

#include <codecvt>
#include <iostream>
#include <fstream>

MarkovAutomaton::MarkovAutomaton(size_t contextSize): contextSize(contextSize)
{

}

void MarkovAutomaton::UpdateFromString(const std::wstring& text) {
    typedef boost::tokenizer<boost::char_separator<wchar_t>,
            std::wstring::const_iterator, std::wstring> tokenizer;
    boost::char_separator<wchar_t> sep{L" \t.,?!<>\\/\n=:;"};
    tokenizer tok{text, sep};
    TokenIdProcessor idProcessor(this);
    for (tokenizer::iterator itToken = tok.begin(); itToken != tok.end(); ++itToken) {
        std::wstring currentToken = CharToRemove::getInst().tolower_locale(*itToken);
        size_t tokenId;
        const auto itId = word2id.find(currentToken);
        if (itId == word2id.end()) {
            tokenId = word2id.size() + 1;
            word2id[currentToken] = tokenId;
        } else {
            tokenId = itId->second;
        }
        idProcessor.processTokenId(tokenId);
    }
}

MarkovAutomaton::TokenIdProcessor::TokenIdProcessor(MarkovAutomaton *automaton): automaton(automaton),
    currentPolyHash(0), lastDigit(1)
{

}

void MarkovAutomaton::TokenIdProcessor::processTokenId(size_t tokenId) {
    inProgress.push(tokenId);
    size_t nextPolyHash = (currentPolyHash * MULT + tokenId) % MODULO;
    if (inProgress.size() <= automaton->contextSize) {
        lastDigit = (lastDigit * MULT) % MODULO;
    } else {
        size_t idToRemove = inProgress.front();
        inProgress.pop();
        nextPolyHash = (nextPolyHash + MODULO - (idToRemove * lastDigit) % MODULO ) % MODULO;
        ++(automaton->matrix[currentPolyHash][tokenId]);
    }
    currentPolyHash = nextPolyHash;
}

void MarkovAutomaton::SaveIndex(const std::string& flnm) {
    std::ofstream dest(flnm);
    dest << word2id.size() << std::endl;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    for (const auto& word_id: word2id) {
        dest << converter.to_bytes(word_id.first) << " " << word_id.second
             << std::endl;
    }
}

void MarkovAutomaton::SaveMatrix(const std::string& flnm) {
    std::ofstream dest(flnm);

    dest << matrix.size() << std::endl;
    for (const auto& word2hist: matrix) {
        dest << word2hist.first << std::endl;
        dest << "\t" << word2hist.second.size() << std::endl;
        for (const auto& id_freq: word2hist.second) {
            dest << "\t\t" << id_freq.first << " " << id_freq.second << std::endl;
        }
    }
}
