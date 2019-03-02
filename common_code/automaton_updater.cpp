#include "automaton_updater.h"
#include "markov_automaton.h"
#include "typedefs.h"

#include <codecvt>
#include <locale>



template<typename What, typename Context>
AutomatonUpdater<What, Context>::AutomatonUpdater(What *what, Context& context): what(what), context(context) {}

template<typename What, typename Context>
void AutomatonUpdater<What, Context>::operator()(const std::string& s) {
    what->update(context.from_bytes(s));
}

template
AutomatonUpdater<MarkovAutomaton, ConverterType>::AutomatonUpdater(
        MarkovAutomaton *what, ConverterType& context);

template
void AutomatonUpdater<MarkovAutomaton, ConverterType>::operator()(const std::string&);
