/*
 * CTexture.cpp
 *
 *  Created on: 21 марта 2016 г.
 *      Author: kostya_hm
 */

#include "CTexture.h"
#include <SDL_image.h>

CTexture::~CTexture()
{
    if (getTexture() != nullptr)
		SDL_DestroyTexture(getTexture());

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
	{
		if (getTexture() != nullptr)
			SDL_DestroyTexture(getTexture());
        setTexture(Renderer::getInstance()->getTextureFromSurface(surface));
	}
}


void  CTexture::setTexture(SDL_Texture* value)
{
	if (getTexture() != nullptr)
		SDL_DestroyTexture(getTexture());

    texture = value;
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


