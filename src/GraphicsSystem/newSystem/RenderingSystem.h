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

    explicit RenderingSystem(const Size& aScreenSize);
    RenderingSystem() = delete;

    void renderTexture(SDL_Texture *texturePtr, const Size aTextureSize,  const Position &&aDestPosition);



    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>  loadTextureFromFile(const string& filename);
    std::unique_ptr<TTF_Font, void(*)(TTF_Font*)> loadFontFromFile(const string& filename, int size);


    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> getTextureFromSurface(SDL_Surface* surface);


    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> textToTexture(TTF_Font* aFont, const string& aText, SDL_Color&& color);
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> textToTexture(TTF_Font* aFont, const string& aText, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

    void setRendererDrawColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
    void renderClear();
    void renderPresent();

    Size getScreenSize() const;

private:

    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer;
};

