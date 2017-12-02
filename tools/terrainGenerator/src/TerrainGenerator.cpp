#include "TerrainGenerator.hpp"
#include <sstream>
#include "Utility/textfilefunctions.h"
#include <SDL_image.h>

void TileLegendCollection::parseString(const std::string& aLegend)
{
    std::istringstream legendTokens(aLegend);

    legendTokens >> tileSize.width >> tileSize.height;

    std::string atlasCommand;

    legendTokens >> atlasCommand;

    if (atlasCommand == "atlas")
    {
        std::string atlasPath;

        legendTokens >> atlasPath;

        std::cout << "AtlasPath = " << atlasPath << std::endl;
        if (atlasPath != "!none!")
        {
            mIsAtlas = true;
            atlasTexture.loadTexture(atlasPath);
            atlasTexture.scaleToTexture();
        }
    }

    size_t collection_size{0};

    legendTokens >> collection_size;

    std::string tilename;
    std::string tileletter;

    std::map<char, int> tileLetterPathCostMapping;

    for(size_t index = 0; index < collection_size; ++index)
    {
        legendTokens >> tileletter;
        std::cout << "tileletter is = " << tileletter << std::endl;
        legendTokens >> tilename;
        std::cout << "tilename is = " << tilename << std::endl;

        int pathCost{};
        legendTokens >> pathCost;

        tileLetterPathCostMapping[tileletter[0]] = pathCost;

        if (mIsAtlas)
        {
            std::string posX, posY;
            legendTokens >> posX >> posY;
            int x = std::stoi(posX);
            int y = std::stoi(posY);

            std::cout << "TilePos is = " << x << ", " << y << std::endl;
            tileAtlasPositions.emplace(tileletter[0], Position(x, y));
        }
        else
            loadTile(tileletter, tilename, tileSize);
    }

    legendTokens >> rows >> columns;

    matrix.resize(rows);
    pathMatrix.resize(rows);
    for(size_t row = 0; row < rows; ++row)
    {
        std::string str = "";

        pathMatrix[row].resize(columns);
        for(size_t column = 0; column < columns; ++column)
        {
            char symbol = legendTokens.get();
            while(isspace(symbol))
            {
                symbol = legendTokens.get();
            }
            str += symbol;

            pathMatrix[row][column] = tileLetterPathCostMapping.at(symbol);
        }
        std::cout << "string in matrix" << str << std::endl;
        matrix[row] = str;
    }
}

TileLegendCollection::TileLegendCollection(std::shared_ptr<RenderingSystem>& aRenderer)
    : mRenderer(aRenderer)
    , mIsAtlas(false)
    , atlasTexture(mRenderer)
    , tiles()

{
}

size_t TileLegendCollection::size() const
{
    return tiles.size();
}

void TileLegendCollection::loadTile(const std::string tileMapping, const std::string& aTileName, Size aTileSize)
{
    std::string tempPath = "./tiles/" + aTileName + ".png";
    std::cout << "tempPath" << tempPath << std::endl;

    Texture2D texture(mRenderer);
    texture.setSize(aTileSize);
    texture.loadTexture(tempPath);
    tiles.emplace(tileMapping[0], texture);//[aTileName]=texture;
}

//void TileLegendCollection::skipCommentLines(std::istringstream& aStream) TODO: Why not working?
//{
//    auto commentLineChecker = [=](std::istringstream& aStream)
//        {
//            auto str = aStream.str();

//            if (str.empty() || str.length() < 2)
//            {
//                return false;
//            }

//            return str[0] == '-' && str[1] == '-';
//        };

//    while(commentLineChecker(aStream))
//    {
//        std::string uselessString;
//        std::getline(aStream, uselessString);
//    }
//}

Texture2D TileLegendCollection::constructTextureByMap(std::unique_ptr<SDL_Surface, void (*)(SDL_Surface*)>& out)
{
    Texture2D targetTexture(mRenderer);

    targetTexture.setSize(Size(tileSize.width * static_cast<int>(columns), tileSize.height * static_cast<int>(rows)));
    targetTexture.createBlankTexture();
    targetTexture.setAsRenderTarget();

    std::cout << "targetTextureSize " << targetTexture.getSize() << std::endl;
    for(size_t row = 0; row < rows; ++row)
    {
        for(size_t column = 0; column < columns; ++column)
        {
            Position pos{static_cast<int>(column)* tileSize.width, static_cast<int>(row)* tileSize.height};
            std::string line = matrix[row];

            if (mIsAtlas)
            {
                std::cout << "symbolToShow = " << line[column] << '\t';
                Position pos2 = tileAtlasPositions.at(line[column]);
                std::cout << "symbolPos = " << pos2 << std::endl;

                SDL_Rect tileRect{pos2.x, pos2.y, tileSize.width, tileSize.height};
                atlasTexture.drawPartAtPosition(pos, &tileRect);
            }
            else
            {
                tiles.at(line[column]).drawAtPosition(pos);
            }

        }
    }
    out = std::move(mRenderer->createSurfaceFromRenderingTarget(targetTexture.getSize(), Position()));

    targetTexture.unSetAsRenderTarget();
    return targetTexture;
}

std::vector<std::vector<int> > TileLegendCollection::getPathMatrix() const
{
    return pathMatrix;
}

Size TileLegendCollection::getTileSize() const
{
    return tileSize;
}

Texture2D& TileLegendCollection::getTextureByTag(const std::string& aTag)
{
    return tiles.at(aTag[0]);
}

