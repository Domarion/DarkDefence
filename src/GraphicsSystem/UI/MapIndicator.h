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
    void setNormalTexture( const string& filename);

    SDL_Texture*  getCompletedTexture() const;
    void setCompletedTexture( const string& filename);

    SDL_Texture*  getLockedTexture() const;
    void setLockedTexture( const string& filename);

    virtual void draw() override;
    int getIndicatorWidth() const;
    void setIndicatorWidth(int value);

    int getIndicatorHeight() const;
    void setIndicatorHeight(int value);

private:
    CTexture&  textureChoice(int index);
    CTexture normalTexture, completedTexture, lockedTexture;
    int mapCount;
    int currentMapIndex;
    int indicatorWidth, indicatorHeight;
};
