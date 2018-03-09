#pragma once

#include <string>

#include <SDL.h>

#include "Font.h"
#include "RenderingSystem.h"

using std::string;
using std::shared_ptr;

class Texture2D final
{
public:
    Texture2D() = default;
    Texture2D(std::shared_ptr<RenderingSystem>& renderingContext);
    Texture2D(const Texture2D& right);
    virtual ~Texture2D() = default;
    void setTexture(shared_ptr<SDL_Texture> texture);
    void setTextureFromText(const string& aText, Font aFont);

    const shared_ptr<SDL_Texture>& getTexture() const;
    void loadTexture(const string& aFilename);
    void drawAtPosition(Position pos) const;
    void drawAtPositionFlipped(Position aPosition, int aFlipFlags) const;
    void drawAtPositionRotated(Position aDrawPosition, double aRotationAngle, Position aRotationCenter) const;

    void drawPartAtPosition(Position pos, const SDL_Rect* clip, int aFlipFlags = SDL_FLIP_NONE) const;
    void drawScaledPartAtPosition(Position pos, Size aTextureSize, const SDL_Rect* clip) const;
    void drawScaledPartAtPositionFlipping(Position pos, Size aTextureSize, const SDL_Rect* clip, int aFlipFlags) const;

    Size getSize() const;
    void setSize(Size size);
    void scaleToTexture();
    bool hasTexture() const;
    void resetTexture();
    void setAsRenderTarget();
    void unSetAsRenderTarget();
    void createBlankTexture(SDL_TextureAccess aAccess = SDL_TEXTUREACCESS_TARGET);
    Size getOriginalTextureSize() const;

private:

    void setOriginalTextureSize();
    shared_ptr<SDL_Texture> texturePtr;
    Size textureSize; // логический размер
    std::shared_ptr<RenderingSystem> renderer;
    Size originalTextureSize; // реальный размер загруженной текстуры
};

