#pragma once

#include <map>

std::map<std::string, std::string> getParameters(int argc, const char**);
std::string exec(const char* cmd);
std::wstring tolower_locale(const std::wstring s);

void checkMarkovParameters(int argc, const char **argv);
void checkGeneratorParameters(int argc, const char **argv);

std::map<std::string, std::string> getMarkovParameters(int argc, const char **argv);
std::map<std::string, std::string> getGeneratorParameters(int argc, const char **argv);

template <typename WordProcessor>
void callWordProcessor(const std::string& command,
                       const std::string& uri,
                       WordProcessor wordProcessor);
void PrintWord(const std::string &word);
