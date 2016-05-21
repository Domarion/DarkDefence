#pragma once
#include "../CTexture.h"

class MapIndicator: public CTexture
{
public:
    MapIndicator();

    int getCurrentMapIndex() const;
    void setCurrentMapIndex(int value);

    int getMapCount() const;
    void setMapCount(int value);

    SDL_Texture*  getNormalTexture() const;
    void setNormalTexture( SDL_Texture* const value);

    SDL_Texture*  getCompletedTexture() const;
    void setCompletedTexture( SDL_Texture* const value);

    SDL_Texture*  getLockedTexture() const;
    void setLockedTexture( SDL_Texture* const value);
    SDL_Texture*  textureChoice(int index);
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
