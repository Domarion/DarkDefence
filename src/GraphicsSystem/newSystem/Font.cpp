#include "Font.h"
#include "../../Utility/textfilefunctions.h"

Font::Font(shared_ptr<TTF_Font> ttfFont, std::shared_ptr<RenderingSystem>& aRenderer)
    : mRenderer(aRenderer)
    , mFontPtr( ttfFont )
    , mFontColor({0, 0, 0, 255})
    , mFontSize(0)
{
}

Font::Font()
    : mFontPtr(nullptr, TTF_CloseFont)
    , mFontColor({0, 0, 0, 255})
    , mFontSize(0)
{
}

Font::Font(
    const std::string& aFontPath,
    size_t aFontSize,
    Uint8 r,
    Uint8 g,
    Uint8 b,
    std::shared_ptr<RenderingSystem>& aRenderer)
    : mRenderer(aRenderer)
    , mFontPtr(nullptr, TTF_CloseFont)
    , mFontColor({r, g, b, 255})
    , mFontSize(aFontSize)
{
    loadFromFile(aFontPath, aFontSize);
}

void Font::loadFromFile(const std::string& aFilename, size_t aFontSize)
{
    mFontSize = aFontSize;
    setFont(std::move(mRenderer->loadFontFromFile(aFilename, mFontSize)));
}

SDL_Color Font::getFontColor() const
{
    return mFontColor;
}

void Font::setFontColor(const SDL_Color& value)
{
    mFontColor = value;
}

void Font::setFontColor(Uint8 r, Uint8 g, Uint8 b)
{
    mFontColor = {r, g, b, 255};
}

int Font::getFontSize() const
{
    return mFontSize;
}

const shared_ptr<TTF_Font>& Font::getFont() const
{
    return mFontPtr;
}

void Font::setFont(shared_ptr<TTF_Font> aTTFFont)
{
    mFontPtr = aTTFFont;
}
