#include "TileTerrainMaker.h" 
#include <sstream>
#include "../../Utility/textfilefunctions.h"
void TileLegendParser::parseString(const std::string &aLegend, TileLegendCollection &aDestCollection)
{
    std::istringstream legendTokens(aLegend);

    Size tileSize;
    legendTokens >> tileSize.width >> tileSize.height;

    size_t collection_size{0};
    legendTokens >> collection_size;
    std::string tilename;
    for(size_t index = 0; index < collection_size; ++index)
    {
        legendTokens >> tilename;
        tilename = tilename.substr(0, 1);
        aDestCollection.loadTile(tilename, tileSize);
    }
   /* size_t mapSizeRow{0};
    legendTokens >> mapSizeRow;
    std::vector<std::string> map(mapSizeRow);
    for(size_t row = 0; row < mapSizeRow; ++row)
    {
        legendTokens >> map[row];
    }
    aDestCollection.constructTextureByMap(map);*/

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



void TileLegendCollection::loadTile(const std::string& aTileName, Size aTileSize)
{
    std::string tempPath = "GameData/textures/Tiles/" + aTileName + ".png";
    androidText::setRelativePath(tempPath);
    Texture2D texture(mRenderer);
    texture.loadTexture(tempPath);
    texture.setSize(aTileSize);
    tiles.emplace(aTileName,texture);//[aTileName]=texture;
}

//Texture2D TileLegendCollection::constructTextureByMap(std::vector<std::string> &map)
//{
//    return Texture2D(mRenderer);
//}

Texture2D TileLegendCollection::getTextureByTag(const std::string &aTag)
{
    return tiles.at(aTag);
}
