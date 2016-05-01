/*
 * Sprite.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "Sprite.h"
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>


Sprite::Sprite(SDL_Texture* texture, SDL_Rect *sRect)
:CTexture(nullptr, texture, sRect), zOrder(0)
{
}


Sprite::~Sprite()
{
	// TODO Auto-generated destructor stub
}


void Sprite::setZOrder(int value)
{
	zOrder = value;
}

int Sprite::getZOrder() const
{
	return zOrder;

}

void Sprite::setPos(SDL_Point* position)
{
	getRect()->x = position->x;
	getRect()->y = position->y;
}

void Sprite::setPos(int x, int y)
{
	getRect()->x = x;
	getRect()->y = y;
}
/*const Sprite& Sprite::operator =(const Sprite& right)
{
	if (&right != this)
	{

	}
	return *this;
}

Sprite::Sprite(const Sprite& right)
{

}*/
