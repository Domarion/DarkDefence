#pragma once
#include <SDL.h>

#include <string>
using std::string;

#include "Font.h"
#include "RenderingSystem.h"
using std::shared_ptr;

class Texture2D final
{
public:
    Texture2D(std::shared_ptr<RenderingSystem> &renderingContext);
    Texture2D(const Texture2D& right);
    virtual ~Texture2D() = default;
    void setTexture(shared_ptr<SDL_Texture> texture);
    void setTextureFromText(const string& ltext, Font lfont);

    const shared_ptr<SDL_Texture> &getTexture() const;
    void loadTexture(const string& filename, bool aRelativePath = true);
    void drawAtPosition(Position pos) const;
    void drawPartAtPosition(Position pos, const SDL_Rect *clip) const;
    void drawScaledPartAtPosition(Position pos, Size aTextureSize, const SDL_Rect *clip) const;

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

