/*
 * CTexture.cpp
 *
 *  Created on: 21 марта 2016 г.
 *      Author: kostya_hm
 */

#include "CTexture.h"
#include <SDL2/SDL_image.h>
CTexture::~CTexture()
{
    if (getTexture() != nullptr)
		SDL_DestroyTexture(getTexture());

   // if (rect != nullptr)
     //   delete rect;
}

SDL_Renderer* CTexture::getRenderer() const
{
	return renderptr;
}

void CTexture::setRenderer(SDL_Renderer* value)
{
	renderptr = value;
}

SDL_Rect* CTexture::getRect() const
{
	return rect;
}

void CTexture::setRect(SDL_Rect* value)
{
	rect = value;
}

void CTexture::draw()
{
    CopyTextureToRenderer(getTexture(), nullptr, getRect());
	//SDL_RenderCopy(getRenderer(), getTexture(), getRect(), getRect());
}

bool CTexture::hasRenderer() const
{
	return renderptr != nullptr;
}

SDL_Texture*  CTexture::getTexture() const
{
	return texture;
}

CTexture::CTexture(SDL_Renderer *aRenderer , SDL_Texture* aTexture, SDL_Rect* aRect)
:texture(nullptr)
{
	setRenderer(aRenderer);
	setTexture(aTexture);
	setRect(aRect);
}

void CTexture::setTextureFromSurface(SDL_Surface* surface)
{


	if (surface != nullptr)
	{
		if (getTexture() != nullptr)
			SDL_DestroyTexture(getTexture());
		setTexture(SDL_CreateTextureFromSurface(getRenderer(), surface));
	}
}
SDL_Texture* CTexture::getTextureFromSurface(SDL_Surface* surface)
{
	SDL_Texture* texture = nullptr;

	if (surface != nullptr)
	{
		texture = SDL_CreateTextureFromSurface(getRenderer(), surface);
	}
	return texture;
}

void  CTexture::setTexture(SDL_Texture* value)
{
	if (getTexture() != nullptr)
		SDL_DestroyTexture(getTexture());

	texture = value;
}

void CTexture::loadTextureFromFile(std::string filename)
{
	if (getTexture() != nullptr)
		SDL_DestroyTexture(getTexture());

	texture = IMG_LoadTexture(getRenderer(), filename.c_str());
}

void CTexture::CopyTextureToRenderer(SDL_Texture* aTexture,
		SDL_Rect* sourceRect, SDL_Rect* destRect)
{
	if (aTexture != nullptr)
        SDL_RenderCopy(getRenderer(), aTexture, sourceRect, destRect);
}


