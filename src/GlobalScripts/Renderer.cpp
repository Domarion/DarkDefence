#include "Renderer.h"
#include <SDL_image.h>
#include <iostream>
using std::cout;
using std::endl;

Renderer* Renderer::instance_ = nullptr;

Renderer * Renderer::getInstance()
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


SDL_Texture*  Renderer::loadTextureFromFile(std::string filename)
{
    return IMG_LoadTexture(rendererPtr, filename.c_str());
}

SDL_Texture *  Renderer::getTextureFromSurface(SDL_Surface *surface)
{
    SDL_Texture* texture = nullptr;

    if (surface != nullptr)
    {
        texture = SDL_CreateTextureFromSurface(rendererPtr, surface);

    }
    return texture;
}

void Renderer::renderTexture(SDL_Texture*  aTexture, int x, int y, int w, int h, SDL_Rect*  clip)
{
    if (aTexture != nullptr)
    {
        SDL_Rect destRect = {x, y, w, h};
       renderTexture(aTexture,  &destRect, clip);
    }
}

void Renderer::renderTexture(SDL_Texture *  aTexture, const SDL_Rect *  dest, SDL_Rect *  clip)
{
    if (aTexture != nullptr && dest != nullptr)
    {
        SDL_Rect destRect = *dest;
        if (clip != nullptr)
        {
            destRect.w = clip->w;
            destRect.h = clip->h;
        }
        SDL_RenderCopy(rendererPtr, aTexture, clip, &destRect);
    }
}

TTF_Font * Renderer::loadFontFromFile(string filename, int size)
{
    return TTF_OpenFont(filename.c_str(), size);
}

SDL_Texture * Renderer::textToTexture(TTF_Font * font, string text, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Color color = {r, g, b};

    return textToTexture(font, text, color);
}

SDL_Texture * Renderer::textToTexture(TTF_Font * font, string text, SDL_Color color)
{
    SDL_Surface* tempSurface = TTF_RenderUTF8_Solid(font, text.c_str(), color);

    SDL_Texture* resultingTexture = getTextureFromSurface(tempSurface);

    SDL_FreeSurface(tempSurface);

    return resultingTexture;
}


/*SDL_Texture *Renderer::stringToTexture(string text, const CFont &font)
{
    return stringToTexture(font.getFont(),text, font.getFontColor());
}*/

SDL_Texture * Renderer::textToTexture(string fontFilename, int size, string text, Uint8 r, Uint8 g, Uint8 b)
{
    TTF_Font* font = loadFontFromFile(fontFilename, size);
    return textToTexture(font, text, r, g, b);
}

void Renderer::setRendererDrawColor(Uint8 r, Uint8 g, Uint8 b)
{
    const Uint8 alpha = 255;
    SDL_SetRenderDrawColor(rendererPtr, r, g, b, alpha);

}

void Renderer::renderClear()
{
    SDL_RenderClear(rendererPtr);
}

void Renderer::renderPresent()
{
    SDL_RenderPresent(rendererPtr);
}

int Renderer::getScreenWidth()
{
    int w = 0, h = 0;
    SDL_GetWindowSize(windowPtr, &w, &h);

    return w;
}

int Renderer::getScreenHeight()
{
    int w = 0, h = 0;
    SDL_GetWindowSize(windowPtr, &w, &h);

    return h;
}

