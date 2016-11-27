#pragma once
#include <SDL2/SDL_ttf.h>
#include <string>
using std::string;

class CFont
{
public:

    explicit CFont(TTF_Font* ttfFont = nullptr);
    //CFont(const CFont& right);

    CFont(string fontPath, int size, Uint8 r, Uint8 g, Uint8 b);
    ~CFont();

    void loadFromFile(string filename, int size);
    SDL_Color getFontColor() const;
    void setFontColor(const SDL_Color &value);
    void setFontColor(Uint8 r, Uint8 g, Uint8 b);
    int getFontSize() const;

    TTF_Font *getFont() const;
    void setFont(TTF_Font *value);

private:
    TTF_Font* font;
    SDL_Color fontColor;
    int fontSize;
};

