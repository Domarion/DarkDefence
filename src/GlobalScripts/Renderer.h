#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "../GraphicsSystem/CFont.h"
using std::string;

class Renderer
{
public:
    static Renderer* getInstance();
    void initRenderer(int w, int h);
    void destroyRenderer();
    SDL_Texture*  loadTextureFromFile(string filename);
    SDL_Texture*  getTextureFromSurface(SDL_Surface* surface);
    void renderTexture(SDL_Texture*  aTexture, int x, int y, int w, int h, SDL_Rect*  clip = nullptr);
    void renderTexture(SDL_Texture*  aTexture, const SDL_Rect*  dest = nullptr, SDL_Rect*  clip = nullptr);

    TTF_Font*  loadFontFromFile(string filename, int size);
    SDL_Texture * stringToTexture(TTF_Font * font, string text, SDL_Color color);

    SDL_Texture*  stringToTexture(TTF_Font* font, string text, Uint8 r, Uint8 g, Uint8 b);
    SDL_Texture*  stringToTexture(string text, const CFont& font);
    SDL_Texture* stringToTexture(string fontFilename, int size, string text, Uint8 r, Uint8 g, Uint8 b);
    void setRendererDrawColor(Uint8 r, Uint8 g, Uint8 b);
    void renderClear();
    void renderPresent();

    int getScreenWidth();
    int getScreenHeight();
private:
    Renderer();
    ~Renderer();
    static Renderer* instance_;

    SDL_Window* windowPtr;
    SDL_Renderer* rendererPtr;
};

