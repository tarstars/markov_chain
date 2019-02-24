#ifndef DISCRETE_DISTRIBUTION_H
#define DISCRETE_DISTRIBUTION_H

#include <iostream>
#include <vector>

class DiscreteDistribution {
public:
    DiscreteDistribution();
    static DiscreteDistribution createFromStream(std::istream& is);
private:
    std::vector<double> cumulativeDensity;
    std::vector<size_t> tokenIds;
};

#endif // DISCRETE_DISTRIBUTION_H
