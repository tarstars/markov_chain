#pragma once

#include <string>

template<typename What, typename Context>
class AutomatonUpdater {
public:
    AutomatonUpdater(What *what, Context& context);
    void operator()(const std::string& s);
private:
    What *what;
    Context& context;
};
