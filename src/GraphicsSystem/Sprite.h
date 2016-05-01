/*
 * Sprite.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "CTexture.h"

class Sprite : public CTexture
{
public:
	Sprite(SDL_Texture* texture = nullptr, SDL_Rect *sRect = nullptr);
	virtual ~Sprite();

	void setZOrder(int value);
	int getZOrder() const;
	void setPos(SDL_Point* position);
	void setPos(int x, int y);
	//const Sprite& operator=(const Sprite& right);
	//Sprite(const Sprite& right);
private:
	int zOrder;
};
