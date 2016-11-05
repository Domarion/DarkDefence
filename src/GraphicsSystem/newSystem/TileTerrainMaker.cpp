#include "TileTerrainMaker.h" 
#include <sstream>
#include "../../Utility/textfilefunctions.h"
#include <SDL_image.h>
void TileLegendCollection::parseString(const std::string &aLegend)
{
    std::istringstream legendTokens(aLegend);

    legendTokens >> tileSize.width >> tileSize.height;

    size_t collection_size{0};
    legendTokens >> collection_size;
    std::string tilename;
    std::string tileletter;

    for(size_t index = 0; index < collection_size; ++index)
    {
        legendTokens >> tileletter;
        std::cout << "tileletter is = " << tileletter << std::endl;
        legendTokens >> tilename;
        std::cout << "tilename is = " << tilename << std::endl;

        loadTile(tileletter, tilename, tileSize);
    }

    legendTokens >> rows >> columns;
    matrix.resize(rows);

    for(size_t row = 0; row < rows; ++row)
    {
        std::string str = "";

        for(size_t column = 0; column < columns; ++column)
        {
            char symbol = legendTokens.get();
            while(isspace(symbol))
            {
               symbol = legendTokens.get();
            }
            str += symbol;
        }
        std::cout << "string in matrix" << str << std::endl;
        matrix[row] = str;
    }
}

TileLegendCollection::TileLegendCollection(std::shared_ptr<RenderingSystem> &aRenderer)
    : mRenderer(aRenderer)
    , tiles()
{

}

size_t TileLegendCollection::size() const
{
    return tiles.size();
}

void TileLegendCollection::loadTile(const std::string tileMapping, const std::string& aTileName, Size aTileSize)
{
    std::string tempPath = "GameData/textures/Tiles/" + aTileName + ".png";
    std::cout << "tempPath" << tempPath << std::endl;

    Texture2D texture(mRenderer);
    texture.setSize(aTileSize);
    texture.loadTexture(tempPath);
    tiles.emplace(tileMapping[0], texture);//[aTileName]=texture;
}

Texture2D TileLegendCollection::constructTextureByMap(std::unique_ptr<SDL_Surface, void (*)(SDL_Surface *)>& out)
{
    Texture2D targetTexture(mRenderer);

    targetTexture.setSize(Size(tileSize.width * columns, tileSize.height * rows));
    targetTexture.createBlankTexture();
    targetTexture.setAsRenderTarget();

    for(size_t row = 0; row < rows; ++row)
    {
        for(size_t column = 0; column < columns; ++column)
        {
            Position pos{column * tileSize.width, row * tileSize.height};
            std::string line = matrix[row];
            std::cout << "character is = " << line[column] << std::endl;
            tiles.at(line[column]).drawAtPosition(pos);

        }
    }
    out = std::move(mRenderer->createSurfaceFromRenderingTarget(targetTexture.getSize(), Position()));
//   std::string destPath = "/home/kostya_hm/terrain.png";

//    SDL_Surface* outputSurf =  mRenderer->createSurfaceFromRenderingTarget(targetTexture.getSize(), Position()).release();

//    if (outputSurf == nullptr)
//        std::cout << "surface is nullptr" << std::endl;
//    if (IMG_SavePNG(outputSurf, destPath.c_str())!= 0)
//    {
//        std::cout << "SDL has error " << IMG_GetError() << std::endl;
//    }
//    SDL_FreeSurface(outputSurf);

    targetTexture.unSetAsRenderTarget();
    return targetTexture;
}

Texture2D& TileLegendCollection::getTextureByTag(const std::string &aTag)
{
    return tiles.at(aTag[0]);
}
