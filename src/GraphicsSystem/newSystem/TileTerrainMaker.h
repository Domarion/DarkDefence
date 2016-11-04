#pragma once
#include <string>
#include <unordered_map>
#include "Texture2D.h"
#include <vector>

class TileLegendCollection
{
public:
    TileLegendCollection(std::shared_ptr<RenderingSystem>& aRenderer);
    void parseString(const std::string& aLegend);

    size_t size() const;
    Texture2D& getTextureByTag(const std::string& aTag);
    Texture2D constructTextureByMap();

private:
    void loadTile(const std::string tileMapping, const std::string &aTileName, Size aTileSize);

    std::shared_ptr<RenderingSystem> mRenderer;

    std::unordered_map<char, Texture2D> tiles;
    std::vector<std::string> matrix;
    size_t rows{};
    size_t columns{};
    Size tileSize{};
};
