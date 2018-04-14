#include <iostream>

#include "PathMapGenerator.hpp"
#include <cstring>

// This tool for conversion from Tiled json format to path map.
int main(int argc, const char** argv)
{
    if (argc == 1 && strncmp(argv[1], "help", 5) == 0)
    {
        std::cout << "HELP: First argument is full path to tiled file second - full path to output pathmap config" << std::endl;
        return 0;
    }

    if (argc != 3)
    {
        std::cerr << "wrong argument count. Expected 2" << std::endl;
        return 1;
    }

    std::string tiledFilePath = argv[1];
    std::string outputFilePath = argv[2];
    
    PathMapGenerator generator;
    generator.loadConfig(tiledFilePath);
    generator.savePathMap(outputFilePath);
    
    return 0;
}
