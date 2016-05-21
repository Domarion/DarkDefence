#include "MapIndicator.h"
#include "../../GlobalScripts/Renderer.h"
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

SDL_Texture*  MapIndicator::getNormalTexture() const
{
    return normalTexture.getTexture();
}

void MapIndicator::setNormalTexture(const string& filename)
{
    normalTexture.loadTexture(filename);
}

SDL_Texture*  MapIndicator::getCompletedTexture() const
{
    return completedTexture.getTexture();
}

void MapIndicator::setCompletedTexture(const string& filename)
{
    completedTexture.loadTexture(filename);
}

SDL_Texture*  MapIndicator::getLockedTexture() const
{
    return lockedTexture.getTexture();
}

void MapIndicator::draw()
{
    int x = getRect().x;
    int y = getRect().y;

    for(int i = 0; i < mapCount; x += indicatorWidth, ++i)
    {

        Renderer::getInstance()->renderTexture(textureChoice(i).getTexture(), x, y, indicatorWidth, indicatorHeight);
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

void MapIndicator::setLockedTexture(const string& filename)
{
    lockedTexture.loadTexture(filename);
}

CTexture& MapIndicator::textureChoice(int index)
{
    if (index > currentMapIndex)
        return lockedTexture;

    if (index < currentMapIndex)
        return completedTexture;

    return normalTexture;
}


