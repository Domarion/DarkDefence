#include "TerrainGenerator.hpp"
#include "SDL_Engine.h"
#include "Utility/textfilefunctions.h"
#include <SDL_image.h>
#include <fstream>

void saveTerrain(std::string filename, std::string outputFilePath);


void saveTerrain(std::string filename, std::string outputFilePath)
{
    Size scrnSize = Size(800, 480);
    auto renderer = std::make_shared<RenderingSystem>(scrnSize);
    TileLegendCollection tileCollection(renderer);

    std::string str;
    androidText::loadTextFileToString(filename, str, false);
    tileCollection.parseString(str);
    using TSurfaceDeleter = void (*)(SDL_Surface *);

    std::unique_ptr<SDL_Surface, TSurfaceDeleter> surface(nullptr, [](SDL_Surface* aSurface){SDL_FreeSurface(aSurface);});
    Texture2D targetTexture = tileCollection.constructTextureByMap(surface);

    if (surface == nullptr || surface.get() == nullptr)
        std::cerr << "surface is nullptr" << std::endl;
    if (IMG_SavePNG(surface.get(), outputFilePath.c_str())!= 0)
    {
        std::cerr << "SDL has error " << IMG_GetError() << std::endl;
    }

    Size tileSize =  tileCollection.getTileSize();

    auto pathMatrix = tileCollection.getPathMatrix();

    std::ofstream pathFile(outputFilePath + ".txt");

    pathFile << pathMatrix.size() << '\t' << pathMatrix[0].size() << std::endl;
    for(const auto& line : pathMatrix)
    {
        pathFile << line[0];

        for(size_t index = 1; index < line.size(); ++index)
        {
            pathFile << '\t' << line[index];
        }

        pathFile << std::endl;
    }
    pathFile << tileSize.width << '\t' << tileSize.height;

    pathFile.close();
//    renderer->renderClear();
//    targetTexture.drawAtPosition(Position());
//    renderer->renderPresent();
//    SDL_Delay(3000);
}


int main(int argc, const char** argv)
{
    if (argc == 1 && strcmp(argv[1], "help") == 0)
    {
        std::cout << "HELP: First argument is full path to config file second - full path to output png image" << std::endl;
        return 0;
    }

    if (argc != 3)
    {
        std::cerr << "wrong argument count. Expected 2" << std::endl;
        return 1;
    }

    SDL2Engine::SDL2(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    std::string configFile = argv[1];
    std::string outputFile = argv[2];
    saveTerrain(configFile, outputFile);
    return 0;
}
