#include "random_singleton.h"

RandomSingleton::RandomSingleton(): rd(), gen(rd()), dis(0, 1)
{

}

double RandomSingleton::rand() {
    static RandomSingleton singleton;
    return singleton.dis(singleton.gen);
}
