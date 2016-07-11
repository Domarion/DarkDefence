/*
 * ProgressBar.cpp
 *
 *  Created on: 21 марта 2016 г.
 *      Author: kostya_hm
 */

#include "ProgressBar.h"

ProgressBar::ProgressBar()
:CTexture(), frontTexture(nullptr)
{
	// TODO Auto-generated constructor stub
    setFrontRect(0, 0, 0 , 0);
}

ProgressBar::~ProgressBar()
{

   // if (getFrontTexture() != nullptr)
     //   SDL_DestroyTexture(getFrontTexture());

	// TODO Auto-generated destructor stub
}

const SDL_Rect& ProgressBar::getFrontRect() const
{
    return frontTexture.getRect();
}

void ProgressBar::calculateFront(int current, int max)
{
    if (max != 0)
    {
        SDL_Rect rect = frontTexture.getRect();
        rect.w = static_cast<int>(getRect().w * (current+0.0)/max);
        frontTexture.setRect(rect);
    }
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
    frontTexture.setRect(value);

}

void ProgressBar::setFrontRect(int x, int y, int w, int h)
{
    frontTexture.setRect(x, y, w, h);
}

void ProgressBar::setPosX(int x)
{
    CTexture::setPosX(x);
    frontTexture.setPosX(x);

}

void ProgressBar::setPosY(int y)
{
    CTexture::setPosY(y);
    frontTexture.setPosY(y);


}

void ProgressBar::setPos(int x, int y)
{
    setPosX(x);
    setPosY(y);
}

SDL_Texture* ProgressBar::getFrontTexture() const
{
    return frontTexture.getTexture();
}

void ProgressBar::setFrontTexture(SDL_Texture* frontTexture)
{
    this->frontTexture.setTexture( frontTexture);
}

void ProgressBar::draw()
{
	CTexture::draw();
    frontTexture.draw();

       // if (frontTexture != nullptr)
        //{
           // Renderer::getInstance()->renderTexture(frontTexture, &frontRect);
       // }
  //  CopyTextureToRenderer( nullptr, );

}
