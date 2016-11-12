#pragma once

#include <string>
#include <unordered_map>
#include "GraphicsSystem/newSystem/Texture2D.h"
#include <vector>


class TileLegendCollection
{
public:
    explicit TileLegendCollection(std::shared_ptr<RenderingSystem>& aRenderer);
    void parseString(const std::string& aLegend);

    size_t size() const;
    Texture2D& getTextureByTag(const std::string& aTag);
    Texture2D constructTextureByMap(std::unique_ptr<SDL_Surface, void (*)(SDL_Surface *)>& out);

private:
    void loadTile(const std::string tileMapping, const std::string &aTileName, Size aTileSize);

    std::shared_ptr<RenderingSystem> mRenderer;

    bool mIsAtlas;
    std::unordered_map<char, Position> tileAtlasPositions;

    Texture2D atlasTexture;
    std::unordered_map<char, Texture2D> tiles;
    std::vector<std::string> matrix;
    size_t rows{};
    size_t columns{};
    Size tileSize{};
};

