#pragma once
#include <string>
#include <unordered_map>
#include "Texture2D.h"
#include <vector>

class TileLegendCollection
{
public:
    TileLegendCollection(std::shared_ptr<RenderingSystem>& aRenderer);
    size_t size() const;
    void loadTile(const std::string &aTileName, Size aTileSize);
    Texture2D getTextureByTag(const std::string& aTag);
//    Texture2D constructTextureByMap(std::vector<std::string>& map);

private:
    std::shared_ptr<RenderingSystem> mRenderer;

    std::unordered_map<std::string, Texture2D> tiles;
};


class TileLegendParser
{
public:
    void parseString(const std::string& aLegend, TileLegendCollection& aDestCollection);
};
