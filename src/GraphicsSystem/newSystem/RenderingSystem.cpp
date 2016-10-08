#include "RenderingSystem.h"
#include "UtilityStructs.h"
#include <SDL_image.h>


RenderingSystem::RenderingSystem(const Size &aScreenSize)
    :   window(nullptr, [](SDL_Window* aWindow){SDL_DestroyWindow(aWindow);})
,   renderer(nullptr, [](SDL_Renderer* aRenderer){SDL_DestroyRenderer(aRenderer);})
{
    window.reset(SDL_CreateWindow("GameApp", 0, 0, aScreenSize.width, aScreenSize.height, SDL_WINDOW_SHOWN));

    if (window != nullptr)
        renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
}

    void RenderingSystem::renderTexture(SDL_Texture* texturePtr, const Size aTextureSize,  const Position &&aDestPosition)
    {
        SDL_Rect destRect = {aDestPosition.x, aDestPosition.y, aTextureSize.width, aTextureSize.height};
        SDL_RenderCopy(renderer.get(), texturePtr, nullptr, &destRect);
    }

    std::unique_ptr<SDL_Texture, void (*)(SDL_Texture *)> RenderingSystem::loadTextureFromFile(const std::string &filename)
    {
        return std::unique_ptr<SDL_Texture, void (*)(SDL_Texture *)>(IMG_LoadTexture(renderer.get(), filename.c_str()),  [](SDL_Texture* aTexture){SDL_DestroyTexture(aTexture);});
    }

    std::unique_ptr<TTF_Font, void (*)(TTF_Font *)> RenderingSystem::loadFontFromFile(const std::string &filename, int size)
    {
        return std::unique_ptr<TTF_Font, void (*)(TTF_Font *)>(TTF_OpenFont(filename.c_str(), size), [](TTF_Font* aFont){TTF_CloseFont(aFont);});
    }

    std::unique_ptr<SDL_Texture, void (*)(SDL_Texture *)> RenderingSystem::getTextureFromSurface(SDL_Surface *surface)
    {
        return std::unique_ptr<SDL_Texture, void (*)(SDL_Texture *)>(SDL_CreateTextureFromSurface(renderer.get(), surface),  [](SDL_Texture* aTexture){SDL_DestroyTexture(aTexture);});

    }

    std::unique_ptr<SDL_Texture, void (*)(SDL_Texture *)> RenderingSystem::textToTexture(TTF_Font *aFont, const std::__cxx11::string &aText, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha)
    {
        SDL_Color color = {red, green, blue, alpha};
        return textToTexture(aFont,aText, std::move(color));
    }

    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> RenderingSystem::textToTexture(TTF_Font* aFont, const string& aText, SDL_Color &&color)
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


