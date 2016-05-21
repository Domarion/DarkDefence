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
: texture(nullptr)
{
    setTexture(aTexture);
    setRect(newRect);
}


CTexture::CTexture(SDL_Texture* aTexture)
: texture(nullptr)
{
    setTexture(aTexture);
    setRect(0, 0, 0 , 0);
}

CTexture::CTexture(const string& filename)
{
    loadTexture(filename);

}


void CTexture::draw()
{

    Renderer::getInstance()->renderTexture(getTexture(), &rect);

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
    free();

    texture = value;
}

void CTexture::setTextureFromText(const string &text, const CFont& font)
{
    setTexture(Renderer::getInstance()->stringToTexture(text, font));
    autoScale();
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


