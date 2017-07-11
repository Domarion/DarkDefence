#pragma once

#include <SDL_ttf.h>
#include <string>
using std::string;
#include <memory>
using std::shared_ptr;
#include "RenderingSystem.h"

class Font final
{
public:
    explicit Font(shared_ptr<TTF_Font> ttfFont, std::shared_ptr<RenderingSystem>& aRenderer);
    Font();

    Font(string fontPath, size_t aFontSize, Uint8 r, Uint8 g, Uint8 b, std::shared_ptr<RenderingSystem>& aRenderer);
    ~Font() = default;

    void loadFromFile(string filename, size_t aFontSize);
    SDL_Color getFontColor() const;
    void setFontColor(const SDL_Color &value);
    void setFontColor(Uint8 r, Uint8 g, Uint8 b);
    int getFontSize() const;

    const shared_ptr<TTF_Font>& getFont() const;
    void setFont(shared_ptr<TTF_Font> aTTFFont);
private:
    std::shared_ptr<RenderingSystem> mRenderer;
    shared_ptr<TTF_Font> mFontPtr;
    SDL_Color mFontColor;
    size_t mFontSize;
};
