/*
 * Label.cpp
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#include "Label.h"



Label::Label(const string &lText, const CFont &lFont)
 : text(lText),font(lFont), texture()
{

}

Label::Label(const string& lText)
: text(lText),font(), texture()
{

}
Label::Label()
: Label("none")
{

}

Label::~Label()
{

}

void Label::draw()
{
    texture.draw();
}

const SDL_Rect &Label::getRect() const
{
    return texture.getRect();
}

void Label::setRect(const SDL_Rect &rect)
{
    texture.setRect(rect);
}

void Label::setRect(int x, int y, int w, int h)
{
    texture.setRect(x, y, w, h);
}

void Label::setPos(int x, int y)
{
    texture.setPos(x, y);
}

void Label::setTexture(SDL_Texture *value)
{
    texture.setTexture(value);
}

SDL_Texture *Label::getTexture() const
{
    return texture.getTexture();
}

void Label::loadTexture(const string& filename)
{
    texture.loadTexture(filename);
}




string Label::getText() const
{
	return text;
}

void Label::setText(const string& value)
{
    if (text != value)
    {
        text = value;
        texture.setTextureFromText(text, font);
    }
}

void Label::setFont(const CFont &value)
{
    font = value;
}

void Label::setPosX(int x)
{
    texture.setPosX(x);
}

void Label::setPosY(int y)
{
    texture.setPosY(y);
}

