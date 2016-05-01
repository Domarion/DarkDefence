#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using std::string;

class Renderer
{
public:
    static Renderer* const getInstance();
    void initRenderer(int w, int h);
    void destroyRenderer();
    SDL_Texture* const loadTextureFromFile(string filename);
    SDL_Texture* const getTextureFromSurface(SDL_Surface* surface);
    void renderTexture(SDL_Texture* const aTexture, int x, int y, int w, int h, SDL_Rect* const clip = nullptr);
    void renderTexture(SDL_Texture* const aTexture, const SDL_Rect* const dest = nullptr, SDL_Rect* const clip = nullptr);

    TTF_Font* const loadFontFromFile(string filename, int size);
    SDL_Texture* const stringToTexture(TTF_Font* const font, string text, int r, int g, int b);
    SDL_Texture* const stringToTexture(string fontFilename, int size, string text, int r, int g, int b);

    void renderClear();
    void renderPresent();
private:
    Renderer();
    ~Renderer();
    static Renderer* instance_;

    SDL_Window* windowPtr;
    SDL_Renderer* rendererPtr;
};

