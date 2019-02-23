#ifndef UTIL_H
#define UTIL_H

#include <map>

std::map<std::string, std::string> getParameters(int argc, const char**);
std::string exec(const char* cmd);

#endif // UTIL_H
