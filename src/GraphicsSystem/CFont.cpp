#include "CFont.h"
#include "../GlobalScripts/Renderer.h"
#include "../Utility/textfilefunctions.h"

CFont::CFont(TTF_Font *ttfFont)
    :font( ttfFont ), fontColor({0, 0, 0, 255}), fontSize(0)
{
}

/*CFont::CFont(const CFont &right)
{
    font = right.font;
    fontColor = right.fontColor;
    fontSize = right.fontSize;
}*/

CFont::~CFont()
{
   TTF_CloseFont(font);
   font = nullptr;
}

void CFont::loadFromFile(string filename, int size)
{
    fontSize = size;
    string filename1 = filename;
    androidText::setRelativePath(filename1);
    setFont(Renderer::getInstance()->loadFontFromFile(filename1, size));
}

SDL_Color CFont::getFontColor() const
{
    return fontColor;
}

void CFont::setFontColor(const SDL_Color &value)
{
    fontColor = value;
}

void CFont::setFontColor(Uint8 r, Uint8 g, Uint8 b)
{
    fontColor = {r, g, b, 255};
}

int CFont::getFontSize() const
{
    return fontSize;
}

TTF_Font *CFont::getFont() const
{
    return font;

}

void CFont::setFont(TTF_Font *value)
{
    font = value;
}
