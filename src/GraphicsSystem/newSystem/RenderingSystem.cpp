#include "RenderingSystem.h"
#include "UtilityStructs.h"
#include <SDL_image.h>


RenderingSystem::RenderingSystem(const Size &aScreenSize)
    : window
      (
           SDL_CreateWindow(
               "GameApp",
               0,
               0,
               aScreenSize.width,
               aScreenSize.height,
               SDL_WINDOW_SHOWN),
           [](SDL_Window* aWindow){SDL_DestroyWindow(aWindow);}
      )
    , renderer
      (
        SDL_CreateRenderer
        (
            window.get(),
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
        ),
        [](SDL_Renderer* aRenderer){SDL_DestroyRenderer(aRenderer);}
      )
{
    SDL_GetDisplayDPI(0, &mDdpi, nullptr, nullptr);
}

void RenderingSystem::renderTexture(SDL_Texture* texturePtr, Size aTextureSize,  Position aDestPosition)
{
    SDL_Rect destRect = {aDestPosition.x, aDestPosition.y, aTextureSize.width, aTextureSize.height};
    SDL_RenderCopy(renderer.get(), texturePtr, nullptr, &destRect);
}

void RenderingSystem::renderTexture(SDL_Texture* texturePtr, Position aDestPosition, const SDL_Rect* clipRect)
{
    if (texturePtr != nullptr && clipRect != nullptr)
    {
        SDL_Rect destRect = {aDestPosition.x, aDestPosition.y, clipRect->w, clipRect->h};

//        std::cout << "DEST Rect = " << destRect.x  << "\t" << destRect.y
//                  << "\t" << destRect.w << "\t" << destRect.h << std::endl;

//        std::cout << "Clip Rect = " << clipRect->x  << "\t" << clipRect->y
//                  << "\t" << clipRect->w << "\t" << clipRect->h << std::endl;


        SDL_RenderCopy(renderer.get(), texturePtr, clipRect, &destRect);
    }
}

void RenderingSystem::renderTextureFlipping(
    SDL_Texture* texturePtr, Position aDestPosition, const SDL_Rect* clipRect, SDL_RendererFlip aFlipFlags)
{
    if (texturePtr != nullptr && clipRect != nullptr)
    {
        SDL_Rect destRect = {aDestPosition.x, aDestPosition.y, clipRect->w, clipRect->h};

        SDL_RenderCopyEx(renderer.get(), texturePtr, clipRect, &destRect, 0.0, nullptr, aFlipFlags);
    }
}

void RenderingSystem::renderTextureRotate(
    SDL_Texture* texturePtr, Position aDestPosition, const SDL_Rect* clipRect, double anAngle)
{
    if (texturePtr != nullptr && clipRect != nullptr)
    {
        SDL_Rect destRect = {aDestPosition.x, aDestPosition.y, clipRect->w, clipRect->h};
        SDL_RendererFlip flipFlagNone = static_cast<SDL_RendererFlip>(SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer.get(), texturePtr, clipRect, &destRect, anAngle, nullptr, flipFlagNone);
    }
}

std::unique_ptr<SDL_Texture, RenderingSystem::TTextureDeleter> RenderingSystem::loadTextureFromFile(
        const std::string& filename)
{
    if (renderer == nullptr)
       throw std::runtime_error("renderer is null, cannot load texture from file");

    return std::unique_ptr<SDL_Texture, TTextureDeleter>(
        IMG_LoadTexture(renderer.get(), filename.c_str()),
        [](SDL_Texture* aTexture){SDL_DestroyTexture(aTexture);});
}

std::unique_ptr<TTF_Font, RenderingSystem::TFontDeleter> RenderingSystem::loadFontFromFile(
    const std::string &filename, int size)
{
    return std::unique_ptr<TTF_Font, RenderingSystem::TFontDeleter>(
        TTF_OpenFont(filename.c_str(), size), [](TTF_Font* aFont){TTF_CloseFont(aFont);});
}

std::unique_ptr<SDL_Texture, RenderingSystem::TTextureDeleter> RenderingSystem::getTextureFromSurface(
    SDL_Surface *surface)
{
    return std::unique_ptr<SDL_Texture, TTextureDeleter>(
        SDL_CreateTextureFromSurface(renderer.get(), surface),
        [](SDL_Texture* aTexture){SDL_DestroyTexture(aTexture);});
}

std::unique_ptr<SDL_Texture, RenderingSystem::TTextureDeleter> RenderingSystem::createBlankTexture(
    Size aSize, SDL_TextureAccess aAccess)
{
    return std::unique_ptr<SDL_Texture, RenderingSystem::TTextureDeleter>(
        SDL_CreateTexture(
            renderer.get()
            , SDL_PIXELFORMAT_RGB888
            , aAccess
            , aSize.width
            , aSize.height)
        ,  [](SDL_Texture* aTexture){SDL_DestroyTexture(aTexture);});
}

std::unique_ptr<SDL_Texture, RenderingSystem::TTextureDeleter> RenderingSystem::textToTexture(
    TTF_Font* aFont, const std::string &aText, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
    SDL_Color color = {red, green, blue, alpha};
    return textToTexture(aFont,aText, std::move(color));
}

std::unique_ptr<SDL_Surface, RenderingSystem::TSurfaceDeleter> RenderingSystem::createSurfaceFromRenderingTarget(
    Size aTextureSize, Position aTexturePosition)
{
    SDL_Rect textureRect{aTexturePosition.x, aTexturePosition.y, aTextureSize.width, aTextureSize.height};
    const int bytesPerPixel = 4;
    void* data = SDL_malloc(bytesPerPixel * aTextureSize.width * aTextureSize.height);

    // pitch = texture format bytes * textureWidth
    if (SDL_RenderReadPixels(
        renderer.get(), &textureRect, SDL_PIXELFORMAT_RGB888, data, bytesPerPixel * aTextureSize.width) != 0)
        std::cout << SDL_GetError() << std::endl;

    return std::unique_ptr<SDL_Surface, RenderingSystem::TSurfaceDeleter>(
                SDL_CreateRGBSurfaceWithFormatFrom(data
                                                   , aTextureSize.width
                                                   , aTextureSize.height
                                                   , bytesPerPixel * 8
                                                   , bytesPerPixel * aTextureSize.width
                                                   , SDL_PIXELFORMAT_RGB888)
                , [](SDL_Surface* aSurface){SDL_FreeSurface(aSurface);});
}

void RenderingSystem::renderToTarget(SDL_Texture *texturePtr)
{
    SDL_SetRenderTarget(renderer.get(), texturePtr);
}

std::unique_ptr<SDL_Texture, RenderingSystem::TTextureDeleter> RenderingSystem::textToTexture(
    TTF_Font* aFont, const string& aText, SDL_Color&& color)
{
    SDL_Surface* tempSurface = TTF_RenderUTF8_Solid(aFont, aText.c_str(), color);
    auto resultingTexture = getTextureFromSurface(tempSurface);
    SDL_FreeSurface(tempSurface);

    return resultingTexture;
}

void RenderingSystem::setRendererDrawColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
{
    SDL_SetRenderDrawColor(renderer.get(), red, green, blue, alpha);

}

void RenderingSystem::drawLine(Position aFirstPoint, Position aLastPoint)
{
    SDL_RenderDrawLine(renderer.get(), aFirstPoint.x, aFirstPoint.y, aLastPoint.x, aLastPoint.y);
}

void RenderingSystem::drawGrid(Size aGridSize, Size aCellSize)
{
    int linesCount = (aGridSize.height + 1) / aCellSize.height;
    int columnsCount = (aGridSize.width + 1) / aCellSize.width;

    Position first{0, 0};
    Position last{aGridSize.width, 0};
    for(int line = 0; line < linesCount; ++line)
    {
        drawLine(first, last);
        first.y += aCellSize.height;
        last.y += aCellSize.height;
    }

    first.x = 0;
    first.y = 0;
    last.x = 0;
    last.y = aGridSize.height;

    for(int column = 0; column < columnsCount; ++column)
    {
        drawLine(first, last);
        first.x += aCellSize.width;
        last.x += aCellSize.width;
    }
}

void RenderingSystem::renderClear()
{
    SDL_RenderClear(renderer.get());
}

void RenderingSystem::renderPresent()
{
    SDL_RenderPresent(renderer.get());
}

Size RenderingSystem::getScreenSize() const
{
    Size screenSize;

    SDL_GetWindowSize(window.get(), &screenSize.width, &screenSize.height);

    return screenSize;
}

Size RenderingSystem::getNativeSize() const
{
    return Size{800, 480};
}

double RenderingSystem::getScalingFactor() const //TODO:: Refactor this shit
{
    if (mDdpi >= 100 && mDdpi <= 120)
        return 0.75;
    if (mDdpi <= 180)
        return 1;
    if (mDdpi <= 240)
        return 1.5;
    if (mDdpi <= 280)
        return 2;
    if (mDdpi <= 320)
        return 3;

    if (mDdpi <=480)
        return 4;
    return 0.5;
}

double RenderingSystem::getDPI() const
{
    return mDdpi;
}


