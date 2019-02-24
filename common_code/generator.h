#ifndef GENERATOR_H
#define GENERATOR_H

#include <unordered_map>
#include <vector>

class Generator {
public:
private:
    class WeightIds {
      std::vector<double> cumDist;
      std::vector<size_t> ids;
    };
    std::unordered_map<size_t, WeightIds> data;
};

#endif // GENERATOR_H
