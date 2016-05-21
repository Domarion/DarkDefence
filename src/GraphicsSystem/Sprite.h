/*
 * Sprite.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "CTexture.h"

class Sprite : public CTexture
{
public:
    Sprite(SDL_Texture* texture = nullptr);
	virtual ~Sprite();

	void setZOrder(int value);
	int getZOrder() const;


	//const Sprite& operator=(const Sprite& right);
	//Sprite(const Sprite& right);
private:
	int zOrder;
};
