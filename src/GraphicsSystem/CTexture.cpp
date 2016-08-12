/*
 * CTexture.cpp
 *
 *  Created on: 21 марта 2016 г.
 *      Author: kostya_hm
 */

#include "CTexture.h"
#include <SDL_image.h>
#include "../GlobalScripts/Renderer.h"
#include "../Utility/textfilefunctions.h"
#include <iostream>
CTexture::~CTexture()
{
    free();

}

void CTexture::free()
{
    if (texture != nullptr)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}



CTexture::CTexture(SDL_Texture* aTexture, const SDL_Rect& newRect)
: texture(nullptr), zOrder(0)
{
    setTexture(aTexture);
    setRect(newRect);
}


CTexture::CTexture(SDL_Texture* aTexture)
: texture(nullptr), zOrder(0)
{
    setTexture(aTexture);
    setRect(0, 0, 0, 0);
}

CTexture::CTexture(const string& filename)
{
    loadTexture(filename);

}


void CTexture::draw()
{

    Renderer::getInstance()->renderTexture(getTexture(), &rect);

}

void CTexture::drawPart(SDL_Rect *clip)
{
    Renderer::getInstance()->renderTexture(getTexture(),getRect().x, getRect().y, 0, 0, clip);
}


SDL_Texture* CTexture::getTexture() const
{
	return texture;
}



void CTexture::setTextureFromSurface(SDL_Surface* surface)
{
	if (surface != nullptr)
        setTexture(Renderer::getInstance()->getTextureFromSurface(surface));
}


void  CTexture::setTexture(SDL_Texture* value)
{
    if (value == nullptr)
        return;
    free();

    texture = value;
}

void CTexture::setTextureFromText(string &text, std::shared_ptr<CFont> font)
{
    SDL_Texture* textTexture = Renderer::getInstance()->textToTexture(font.get()->getFont(),text, font.get()->getFontColor());

    if (textTexture != nullptr)
    {
        setTexture(textTexture);
        autoScale();
    }
    else
        std::cout << "CTexture::setTextureFromText texture is null" << std::endl;
}

void CTexture::loadTexture(const string& filename)
{
    string filename1 = filename;
    androidText::setRelativePath(filename1);
    setTexture(Renderer::getInstance()->loadTextureFromFile(filename1));
}

void CTexture::setRect(int x, int y, int w, int h)
{
    rect = {x, y, w, h};
}

void CTexture::setRect(const SDL_Rect &value)
{
    rect = value;
}

const SDL_Rect &CTexture::getRect() const
{
    return rect;
}

void CTexture::setPosX(int x)
{
    rect.x = x;
}

void CTexture::setPosY(int y)
{
    rect.y = y;
}

void CTexture::setPos(int x, int y)
{
    setPosX(x);
    setPosY(y);
}

void CTexture::autoScale()
{
    SDL_QueryTexture(getTexture(), nullptr, nullptr, &rect.w, &rect.h);
}

int CTexture::getZOrder() const
{
    return zOrder;
}

void CTexture::setZOrder(int value)
{
    zOrder = value;
}

void CTexture::setSize(int w, int h)
{
    rect.w = w;
    rect.h = h;
}


