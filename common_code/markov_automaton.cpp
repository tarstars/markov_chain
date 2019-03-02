#include "markov_automaton.h"
#include "util.h"
#include "global_locale.h"

#include <boost/tokenizer.hpp>

#include <codecvt>
#include <iostream>
#include <fstream>
#include <locale>
#include <memory>

class LettersToIgnore {
public:
    bool operator()(wchar_t c) const {
        static std::wstring nonAlphaExceptions = L" \t\n<>=";
        return !std::isalpha(c, *loc) &&  nonAlphaExceptions.find(c) == std::string::npos;
    }
    LettersToIgnore(): loc(GlobalLocale::getLocale())  {}
private:
    std::shared_ptr<const std::locale> loc;
};

MarkovAutomaton::MarkovAutomaton(size_t contextSize): polyHash(contextSize)
{

}

void MarkovAutomaton::update(const std::wstring& text) {
    typedef boost::tokenizer<boost::char_separator<wchar_t>,
            std::wstring::const_iterator, std::wstring> tokenizer;
    std::wstring clearText(text);
    clearText.erase(std::remove_if(clearText.begin(), clearText.end(), LettersToIgnore()), clearText.end());
    boost::char_separator<wchar_t> sep{L" \t.,?!<>\\/\n=:;"};
    tokenizer tok{text, sep};
    for (tokenizer::iterator itToken = tok.begin(); itToken != tok.end(); ++itToken) {
        std::wstring currentToken = tolower_locale(*itToken);
        auto opRes = word2id.emplace(currentToken, word2id.size() + 1);
        size_t tokenId = opRes.first->second;
        processTokenId(tokenId);
    }
}

void MarkovAutomaton::SaveIndex(const std::string& flnm) {
    std::ofstream dest(flnm);
    if (!dest) {
        throw std::runtime_error("can't open file to save index");
    }
    dest << word2id.size() << std::endl;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    for (const auto& word_id: word2id) {
        dest << converter.to_bytes(word_id.first) << " " << word_id.second
             << std::endl;
    }
}

void MarkovAutomaton::SaveMatrix(const std::string& flnm) {
    std::ofstream dest(flnm);
    if (!dest) {
        throw std::runtime_error("can't open file to save matrix");
    }

    dest << polyHash.getContextSize() << std::endl;
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
