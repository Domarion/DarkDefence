/*
 * ProgressBar.cpp
 *
 *  Created on: 21 марта 2016 г.
 *      Author: kostya_hm
 */

#include "ProgressBar.h"

ProgressBar::ProgressBar()
:CTexture(),frontRect(nullptr), frontTexture(nullptr), currentValue(1), maximumValue(1)
{
	// TODO Auto-generated constructor stub

}

ProgressBar::~ProgressBar()
{

    if (getFrontTexture() != nullptr)
        SDL_DestroyTexture(getFrontTexture());

    if (frontRect != nullptr)
        delete frontRect;
	// TODO Auto-generated destructor stub
}

SDL_Rect* ProgressBar::getFrontRect() const
{
	return frontRect;
}

void ProgressBar::calculateFront(int current, int max)
{
    if (frontRect != nullptr && getRect() != nullptr && max != 0)
        frontRect->w = getRect()->w * current/max;
}

void ProgressBar::setRect(SDL_Rect* value)
{
	CTexture::setRect(value);


	/*temp->x = value->x;
	temp->y =value->y;
	temp->h = value->h;*/

    setFrontRect(value);
}

void ProgressBar::setFrontRect(SDL_Rect* frontRect)
{
	this->frontRect = frontRect;
}

SDL_Texture* ProgressBar::getFrontTexture() const
{
	return frontTexture;
}

void ProgressBar::setFrontTexture(SDL_Texture* frontTexture)
{
	this->frontTexture = frontTexture;
}

void ProgressBar::draw()
{
	CTexture::draw();
    CopyTextureToRenderer(getFrontTexture(), nullptr, getFrontRect());

}
