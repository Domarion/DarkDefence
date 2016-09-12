#pragma once
#include <SDL_ttf.h>
#include <string>
using std::string;
#include <memory>
using std::shared_ptr;

class Font final
{

public:
    explicit Font(shared_ptr<TTF_Font> ttfFont);
    Font();

    Font(string fontPath, int size, Uint8 r, Uint8 g, Uint8 b);
    ~Font() = default;

    void loadFromFile(string filename, int size);
    SDL_Color getFontColor() const;
    void setFontColor(const SDL_Color &value);
    void setFontColor(Uint8 r, Uint8 g, Uint8 b);
    int getFontSize() const;

    shared_ptr<TTF_Font> getFont() const;
    void setFont(shared_ptr<TTF_Font> value);
private:
    shared_ptr<TTF_Font> font;
    SDL_Color fontColor;
    int fontSize;
};
