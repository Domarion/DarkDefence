#include "MapIndicator.h"

MapIndicator::MapIndicator()
    :mapCount(0), currentMapIndex(0), indicatorWidth(0), indicatorHeight(0)
{

}

int MapIndicator::getCurrentMapIndex() const
{
    return currentMapIndex;
}

void MapIndicator::setCurrentMapIndex(int value)
{
    currentMapIndex = value;
}

int MapIndicator::getMapCount() const
{
    return mapCount;
}

void MapIndicator::setMapCount(int value)
{
    mapCount = value;
}

SDL_Texture* const MapIndicator::getNormalTexture() const
{
    return normalTexture.getTexture();
}

void MapIndicator::setNormalTexture(SDL_Texture* const value)
{
    normalTexture.setTexture(value);
}

SDL_Texture* const MapIndicator::getCompletedTexture() const
{
    return completedTexture.getTexture();
}

void MapIndicator::setCompletedTexture(SDL_Texture* const value)
{
    completedTexture.setTexture(value);
}

SDL_Texture* const MapIndicator::getLockedTexture() const
{
    return lockedTexture.getTexture();
}

void MapIndicator::draw()
{
    int x = getRect().x;
    int y = getRect().y;

    for(int i = 0; i < mapCount; x += indicatorWidth, ++i)
    {
        Renderer::getInstance()->renderTexture(textureChoice(i), x, y, indicatorWidth, indicatorHeight);
        x += indicatorWidth + 5;
    }
}

int MapIndicator::getIndicatorWidth() const
{
    return indicatorWidth;
}

void MapIndicator::setIndicatorWidth(int value)
{
    indicatorWidth = value;
}

int MapIndicator::getIndicatorHeight() const
{
    return indicatorHeight;
}

void MapIndicator::setIndicatorHeight(int value)
{
    indicatorHeight = value;
}

void MapIndicator::setLockedTexture(SDL_Texture* const value)
{
    lockedTexture.setTexture(value);
}

SDL_Texture* const MapIndicator::textureChoice(int index)
{
    if (index > currentMapIndex)
        return lockedTexture.getTexture();

    if (index < currentMapIndex)
        return completedTexture.getTexture();

    return normalTexture.getTexture();
}


