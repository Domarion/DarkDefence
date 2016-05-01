/*
 * ProgressBar.h
 *
 *  Created on: 21 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../CTexture.h"
#include <SDL2/SDL.h>

class ProgressBar: public CTexture
{
public:
	ProgressBar();
	virtual ~ProgressBar();
	SDL_Rect* getFrontRect() const;
	SDL_Texture* getFrontTexture() const;
	void setFrontTexture(SDL_Texture* frontTexture);
	virtual void draw() override;
	virtual void setRect(SDL_Rect* value) override;
	void calculateFront(int current, int max);
private:
	void setFrontRect(SDL_Rect* frontRect);
	SDL_Rect* frontRect;
	SDL_Texture* frontTexture;
	double currentValue, maximumValue;
};

