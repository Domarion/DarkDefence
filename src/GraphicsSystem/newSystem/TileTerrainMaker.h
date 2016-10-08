#pragma once
#include <string>
#include <unordered_map>
#include "Texture2D.h"
#include <vector>

class TileLegendCollection
{
public:
    size_t size() const;
    void loadTile(const std::string &aTileName, Size aTileSize);
    Texture2D getTextureByTag(const std::string& aTag);
    Texture2D constructTextureByMap(std::vector<std::string>& map);

private:
    std::unordered_map<std::string, Texture2D> tiles;
};


class TileLegendParser
{
public:
    void parseString(const std::string& aLegend, TileLegendCollection& aDestCollection);
};
