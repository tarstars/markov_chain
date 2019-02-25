#include "../common_code/util.h"
#include "../common_code/generation_context.h"
#include "../common_code/generator.h"
#include "../common_code/markov_sampler.h"

#include <iostream>
#include <fstream>


void doMain(int argc, const char **argv) {
    auto cmdParams = getGeneratorParameters(argc, argv);
    std::string modelFilePrefix = cmdParams["model_file_prefix"];
    std::string modelIndexFileName = modelFilePrefix + ".idx";
    std::string modelMatrixFileName = modelFilePrefix + ".mtx";
    std::string startContextsFileName = cmdParams["context_flnm"];

    auto markovSampler = MarkovSampler::loadSampler(modelMatrixFileName, modelIndexFileName);

    std::ifstream startContexts(startContextsFileName);
    if (!startContexts) {
        throw std::runtime_error("can't open start contexts file");
    }
    auto generationContext = GenerationContext::fromStream(startContexts, markovSampler);
    markovSampler.generateFromContext(generationContext);
}

int main(int argc, const char** argv)
{
    try {
        doMain(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        return 1;
    } catch (const std::bad_alloc& err) {
        std::cerr << "memory allocation error" << std::endl;
        return 2;
    }
    return 0;
}
