/*
 * Sprite.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "Sprite.h"



Sprite::Sprite(SDL_Texture* texture)
:CTexture(texture), zOrder(0)
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

