#ifndef RANDOM_SINGLETON_H
#define RANDOM_SINGLETON_H

#include <random>

class RandomSingleton
{
public:
    static double rand();
private:
    RandomSingleton();
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;
};

#endif // RANDOM_SINGLETON_H
