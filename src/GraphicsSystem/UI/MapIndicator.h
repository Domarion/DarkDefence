#pragma once
#include "../CTexture.h"

class MapIndicator: CTexture
{
public:
    MapIndicator();

    int getCurrentMapIndex() const;
    void setCurrentMapIndex(int value);

    int getMapCount() const;
    void setMapCount(int value);

    SDL_Texture* const getNormalTexture() const;
    void setNormalTexture( SDL_Texture* const value);

    SDL_Texture* const getCompletedTexture() const;
    void setCompletedTexture( SDL_Texture* const value);

    SDL_Texture* const getLockedTexture() const;
    void setLockedTexture( SDL_Texture* const value);
    SDL_Texture* const textureChoice(int index);
    virtual void draw() override;
    int getIndicatorWidth() const;
    void setIndicatorWidth(int value);

    int getIndicatorHeight() const;
    void setIndicatorHeight(int value);

private:
    CTexture normalTexture, completedTexture, lockedTexture;
    int mapCount;
    int currentMapIndex;
    int indicatorWidth, indicatorHeight;
};
