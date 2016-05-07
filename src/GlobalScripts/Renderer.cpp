#include "Renderer.h"
#include <SDL2/SDL_image.h>
#include <iostream>
using std::cout;
using std::endl;

Renderer* Renderer::instance_ = nullptr;

Renderer * const Renderer::getInstance()
{
    if (instance_ == nullptr)
        instance_ = new Renderer();

    return instance_;
}

void Renderer::initRenderer(int w, int h)
{
    if (windowPtr == nullptr && rendererPtr == nullptr)
    {
        windowPtr = SDL_CreateWindow("GameApp", 0, 0, w, h, SDL_WINDOW_SHOWN);

        if (windowPtr == nullptr)
            cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        else
        {
            rendererPtr = SDL_CreateRenderer(windowPtr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            if (rendererPtr == nullptr)
                cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;

        }
    }
}

void Renderer::destroyRenderer()
{
    if (rendererPtr != nullptr)
        SDL_DestroyRenderer(rendererPtr);

    if (windowPtr != nullptr)
        SDL_DestroyWindow(windowPtr);
}

Renderer::Renderer()
    :windowPtr(nullptr), rendererPtr(nullptr)
{

}

Renderer::~Renderer()
{
    destroyRenderer();
}


SDL_Texture* const Renderer::loadTextureFromFile(std::string filename)
{
    return IMG_LoadTexture(rendererPtr, filename.c_str());
}

SDL_Texture * const Renderer::getTextureFromSurface(SDL_Surface *surface)
{
    SDL_Texture* texture = nullptr;

    if (surface != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(rendererPtr, surface);

    }
    return texture;
}

void Renderer::renderTexture(SDL_Texture* const aTexture, int x, int y, int w, int h, SDL_Rect* const clip)
{
    if (aTexture != nullptr)
    {
        SDL_Rect destRect = {x, y, w, h};
       renderTexture(aTexture, clip, &destRect);
    }
}

void Renderer::renderTexture(SDL_Texture * const aTexture, const SDL_Rect * const dest, SDL_Rect * const clip)
{
    if (aTexture != nullptr && dest!= nullptr)
    {
        SDL_RenderCopy(rendererPtr, aTexture, clip, dest);
    }
}

TTF_Font * const Renderer::loadFontFromFile(string filename, int size)
{
    return TTF_OpenFont(filename.c_str(), size);
}

SDL_Texture * const Renderer::stringToTexture(TTF_Font * const font, string text, int r, int g, int b)
{
    SDL_Color color = {r, g, b};

    SDL_Surface* tempSurface = TTF_RenderUTF8_Solid(font, text.c_str(), color);

    SDL_Texture* resultingTexture = getTextureFromSurface(tempSurface);

    SDL_FreeSurface(tempSurface);

    return resultingTexture;
}

SDL_Texture * const Renderer::stringToTexture(string fontFilename, int size, string text, int r, int g, int b)
{
    TTF_Font* font = loadFontFromFile(fontFilename, size);
    return stringToTexture(font, text, r, g, b);
}

void Renderer::renderClear()
{
    SDL_RenderClear(rendererPtr);
}

void Renderer::renderPresent()
{
    SDL_RenderPresent(rendererPtr);
}

