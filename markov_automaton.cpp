#include "markov_automaton.h"
#include "locale_services.h"

#include <boost/tokenizer.hpp>

#include <codecvt>
#include <iostream>
#include <fstream>

MarkovAutomaton::MarkovAutomaton(size_t contextSize): polyHash(contextSize)
{

}

void MarkovAutomaton::UpdateFromString(const std::wstring& text) {
    typedef boost::tokenizer<boost::char_separator<wchar_t>,
            std::wstring::const_iterator, std::wstring> tokenizer;
    boost::char_separator<wchar_t> sep{L" \t.,?!<>\\/\n=:;"};
    tokenizer tok{text, sep};
    for (tokenizer::iterator itToken = tok.begin(); itToken != tok.end(); ++itToken) {
        std::wstring currentToken = LocaleServices::getInst().tolower_locale(*itToken);
        size_t tokenId;
        const auto itId = word2id.find(currentToken);
        if (itId == word2id.end()) {
            tokenId = word2id.size() + 1;
            word2id[currentToken] = tokenId;
        } else {
            tokenId = itId->second;
        }
        processTokenId(tokenId);
    }
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

void MarkovAutomaton::processTokenId(size_t id) {
    if (polyHash.ripe()) {
        ++matrix[polyHash.getContextId()][id];
    }
    polyHash.push((id));
}
