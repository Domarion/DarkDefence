#include "TerrainGenerator.hpp"
#include "SDL_Engine.h"
#include "Utility/textfilefunctions.h"

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


//    renderer->renderClear();
//    targetTexture.drawAtPosition(Position());
//    renderer->renderPresent();
//    SDL_Delay(3000);
}


int main(int argc, char** argv)
{
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
