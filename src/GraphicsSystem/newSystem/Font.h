#pragma once

#include <memory>
#include <string>

#include <SDL_ttf.h>

#include "RenderingSystem.h"

using std::string;
using std::shared_ptr;

class Font final
{
public:
    using TFontDeleter = void(*)(TTF_Font*);

    explicit Font(const shared_ptr<TTF_Font>& aTtfFont, std::shared_ptr<RenderingSystem>& aRenderer);
    Font() = default;

    Font(
        const std::string& aFontPath,
        size_t aFontSize,
        Uint8 r,
        Uint8 g,
        Uint8 b,
        std::shared_ptr<RenderingSystem>& aRenderer);
    ~Font() = default;

    void loadFromFile(const std::string& aFilename, size_t aFontSize);
    SDL_Color getFontColor() const;
    void setFontColor(const SDL_Color& value);
    void setFontColor(Uint8 r, Uint8 g, Uint8 b);
    size_t getFontSize() const;

    const shared_ptr<TTF_Font>& getFont() const;
    void setFont(std::unique_ptr<TTF_Font, TFontDeleter>&& aTTFFont);
    void setFont(const shared_ptr<TTF_Font>& aTTFFont);

private:

    std::shared_ptr<RenderingSystem> mRenderer;
    shared_ptr<TTF_Font> mFontPtr;
    SDL_Color mFontColor = {0, 0, 0, 255};
    size_t mFontSize = 0;
};
