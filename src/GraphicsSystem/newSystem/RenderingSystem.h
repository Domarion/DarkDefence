#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
using std::string;
#include <memory>
#include "UtilityStructs.h"

class RenderingSystem
{
public:
    using TTextureDeleter = void (*)(SDL_Texture*);
    using TSurfaceDeleter = void (*)(SDL_Surface*);
    using TFontDeleter = void(*)(TTF_Font*);

    explicit RenderingSystem(const Size& aScreenSize);
    RenderingSystem() = delete;
    RenderingSystem(const RenderingSystem&) = delete;
    RenderingSystem& operator=(const RenderingSystem&) = delete;
    void renderTexture(SDL_Texture* texturePtr, Size aTextureSize, Position aDestPosition);
    void renderTexture(SDL_Texture* texturePtr, Position aDestPosition, const SDL_Rect* clipRect);
    void renderTexture(
        SDL_Texture* texturePtr,
        Size aTextureSize,
        Position aDestPosition,
        const SDL_Rect* clipRect);
    void renderTextureFlipping(
        SDL_Texture* texturePtr, Position aDestPosition, const SDL_Rect* clipRect, SDL_RendererFlip aFlipFlags);
    void renderTextureFlipping(
        SDL_Texture* texturePtr, Position aDestPosition, Size aTextureSize, SDL_RendererFlip aFlipFlags);

    void renderScaledTextureFlipping(
        SDL_Texture* texturePtr,
        Size aTextureSize,
        Position aDestPosition,
        const SDL_Rect* clipRect,
        SDL_RendererFlip aFlipFlags);

    void renderTextureRotate(
        SDL_Texture* texturePtr, Position aDestPosition, const SDL_Rect* clipRect, double anAngle);

    void renderTextureRotate(
        SDL_Texture* texturePtr, Position aDestPosition, Size aTextureSize, double aRotationAngle, Position /*aRotationPosition*/);


    std::unique_ptr<SDL_Texture, TTextureDeleter>  loadTextureFromFile(const string& filename);
    std::unique_ptr<TTF_Font, TFontDeleter> loadFontFromFile(const string& filename, int size);


    std::unique_ptr<SDL_Texture, TTextureDeleter> getTextureFromSurface(SDL_Surface* surface);

    std::unique_ptr<SDL_Texture, TTextureDeleter> createBlankTexture(Size aSize, SDL_TextureAccess aAccess);
    std::unique_ptr<SDL_Texture, TTextureDeleter> textToTexture(
        TTF_Font* aFont, const string& aText, SDL_Color&& color);
    std::unique_ptr<SDL_Texture, TTextureDeleter> textToTexture(
        TTF_Font* aFont, const string& aText, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

    std::unique_ptr<SDL_Surface, TSurfaceDeleter> createSurfaceFromRenderingTarget(
        Size aTextureSize, Position aTexturePosition);
    void renderToTarget(SDL_Texture* texturePtr);

    void setRendererDrawColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
    void drawLine(Position aFirstPoint, Position aLastPoint);
    void drawGrid(Size aGridSize, Size aCellSize);

    void renderClear();

    void renderPresent();

    Size getScreenSize() const;
    Size getNativeSize() const;
    double getScalingFactor() const;
    double getDPI() const;

private:

    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer;
    float mDdpi;
};

