#include "Font.h"
#include "../../Utility/textfilefunctions.h"
#include "../../GlobalScripts/Renderer.h"

Font::Font(shared_ptr<TTF_Font> ttfFont)
:font( ttfFont ), fontColor({0, 0, 0, 255}), fontSize(0)
{

}

Font::Font()
:font(nullptr, TTF_CloseFont), fontColor({0, 0, 0, 255}), fontSize(0)
{

}

Font::Font(string fontPath, int size, Uint8 r, Uint8 g, Uint8 b)
:font(nullptr, TTF_CloseFont), fontColor({r, g, b, 255}), fontSize(size)
{
    loadFromFile(fontPath, size);
}


void Font::loadFromFile(string filename, int size)
{
    fontSize = size;
    string filename1 = filename;
    androidText::setRelativePath(filename1);
    setFont(shared_ptr<TTF_Font>(Renderer::getInstance()->loadFontFromFile(filename1, size), TTF_CloseFont));
}

SDL_Color Font::getFontColor() const
{
    return fontColor;

}

void Font::setFontColor(const SDL_Color &value)
{
    fontColor = value;
}

void Font::setFontColor(Uint8 r, Uint8 g, Uint8 b)
{
    fontColor = {r, g, b, 255};
}

int Font::getFontSize() const
{
   return fontSize;
}

shared_ptr<TTF_Font> Font::getFont() const
{
    return font;
}

void Font::setFont(shared_ptr<TTF_Font> value)
{
    font = value;
}