/*
 * Label.cpp
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#include "Label.h"
#include <iostream>
using std::cout;
using std::endl;


Label::Label(const string& lText)
:CTexture(),lFont(nullptr)
{
	// TODO Auto-generated constructor stub
	setText(lText);

}
Label::Label()
:lFont(nullptr)
{
	setText("");
}

Label::~Label()
{

	if (lFont != nullptr)
    {
       // TTF_CloseFont(lFont);
    }

    // TODO Auto-generated destructor stub
}



string Label::getText() const
{
	return text;
}

void Label::setText(const string& value)
{
	text = value;
	convertTextToTexture();
}


const TTF_Font& Label::getTTFFont() const
{
	return *lFont;//TODO:: nullptr dereference possible...
}

void Label::setTTFFont(TTF_Font* value)
{
	//if (lFont == nullptr)
	//	lFont = new TTF_Font();
    lFont = value;
}

void Label::setFont(TTF_Font *value, int r, int g, int b)
{
    setTTFFont(value);
    setFontColor(r, g, b);
}
void Label::setFont(TTF_Font *value, SDL_Color& color)
{
    setTTFFont(value);
    setFontColor(color);
}

void Label::setFontColor(int r, int g, int b)
{
    fontColor = {r, g, b};
}

void Label::setFontColor(SDL_Color& color)
{
    fontColor = color;
}

void Label::autoScale()
{
    int w, h;
    SDL_QueryTexture(getTexture(), nullptr, nullptr, &w, &h);
    int x = getRect().x;
    int y = getRect().y;
    setRect(x, y, w, h);
}


SDL_Color &Label::getFontColor()
{
    return fontColor;
}




void Label::convertTextToTexture()
{
    if (lFont != nullptr)
	{

        setTexture(Renderer::getInstance()->stringToTexture(lFont, text, fontColor.r, fontColor.g, fontColor.b));
        autoScale();
	}
}
