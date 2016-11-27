#pragma once
#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using std::string;

class Renderer
{
public:

    static Renderer* getInstance();

    void initRenderer(int w, int h);
    void destroyRenderer();



    SDL_Texture*  loadTextureFromFile(string filename);
    TTF_Font*  loadFontFromFile(string filename, int size);


    SDL_Texture*  getTextureFromSurface(SDL_Surface* surface);

    void renderTexture(SDL_Texture*  aTexture, int x, int y, int w, int h, SDL_Rect*  clip = nullptr);
    void renderTexture(SDL_Texture*  aTexture, const SDL_Rect*  dest = nullptr, SDL_Rect*  clip = nullptr);


    SDL_Texture* textToTexture(TTF_Font * font, string text, SDL_Color color);
    SDL_Texture* textToTexture(TTF_Font* font, string text, Uint8 r, Uint8 g, Uint8 b);
    SDL_Texture* textToTexture(string fontFilename, int size, string text, Uint8 r, Uint8 g, Uint8 b);



    void setRendererDrawColor(Uint8 r, Uint8 g, Uint8 b);
    void renderClear();
    void renderPresent();

    int getScreenWidth();
    int getScreenHeight();

    int getDPI() const;
    int DensityPixelToRealPixel(int densityPixel) const;
    int RealPixelToDensityPixel(int realPixel) const;

private:

    Renderer();
    ~Renderer();
    static Renderer* instance_;

    SDL_Window* windowPtr;
    SDL_Renderer* rendererPtr;
    const double minimumDPI = 160.0; //px = dp * (dpi/160)
};

