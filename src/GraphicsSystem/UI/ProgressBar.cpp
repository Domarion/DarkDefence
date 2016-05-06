/*
 * ProgressBar.cpp
 *
 *  Created on: 21 марта 2016 г.
 *      Author: kostya_hm
 */

#include "ProgressBar.h"

ProgressBar::ProgressBar()
:CTexture(), currentValue(1), maximumValue(1)
{
	// TODO Auto-generated constructor stub
    setFrontRect(0, 0, 0 , 0);
}

ProgressBar::~ProgressBar()
{

    if (getFrontTexture() != nullptr)
        SDL_DestroyTexture(getFrontTexture());

	// TODO Auto-generated destructor stub
}

const SDL_Rect& ProgressBar::getFrontRect() const
{
    return frontRect;
}

void ProgressBar::calculateFront(int current, int max)
{
    if (max != 0)
        frontRect.w = getRect().w * current/max;
}

void ProgressBar::setRect(const SDL_Rect& value)
{
    CTexture::setRect(value);

    setFrontRect(value);
}

void ProgressBar::setRect(int x, int y, int w, int h)
{
     CTexture::setRect(x, y, w, h);
     setFrontRect(x, y, w, h);
}

void ProgressBar::setFrontRect(const SDL_Rect& value)
{
    frontRect = value;
}

void ProgressBar::setFrontRect(int x, int y, int w, int h)
{
    frontRect = {x, y, w, h};
}

void ProgressBar::setPosX(int x)
{
    CTexture::setPosX(x);
    frontRect.x = x;
}

void ProgressBar::setPosY(int y)
{
    CTexture::setPosY(y);
    frontRect.y = y;

}

void ProgressBar::setPos(int x, int y)
{
    setPosX(x);
    setPosY(y);
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
    Renderer::getInstance()->renderTexture(getFrontTexture(), &getFrontRect());
  //  CopyTextureToRenderer( nullptr, );

}
