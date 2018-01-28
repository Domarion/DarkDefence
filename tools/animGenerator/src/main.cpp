#include "AnimSaver.hpp"
#include "SDL_Engine.h"
#include <SDL.h>
#include <iostream>

int main(int argc, char** argv)
{
    if (argc == 2 && strcmp(argv[1],"help") == 0)
    {
        std::cout << "HELP: First argument is full path to config file second - full path to output anim" << std::endl;
        return 0;
    }

    if (argc != 3)
    {
        std::cerr << "wrong argument count. Expected 2" << std::endl;
        return 1;
    }

    SDL2Engine::SDL2(SDL_INIT_VIDEO);

    std::string configFile = argv[1];
    std::string outputFile = argv[2];

    AnimSaver saver;

    saver.makeAnim(configFile, outputFile);
    return 0;
}
