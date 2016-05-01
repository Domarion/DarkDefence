/*
 * Camera.cpp
 *
 *  Created on: 24 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "Camera.h"

Camera::Camera(	int xWorldPos, int yWorldPos, int aWidth, int aHeight )
:xWorld( xWorldPos ), yWorld( yWorldPos ), width( aWidth ), height( aHeight )
{
	// TODO Auto-generated constructor stub

}

Camera::~Camera()
{
	// TODO Auto-generated destructor stub
}

SDL_Point Camera::ScreenToWorld(SDL_Point* onScreen)
{

	return ScreenToWorld( onScreen->x, onScreen->y );
}

SDL_Point Camera::WorldToScreen(SDL_Point* inWorld)
{

	return WorldToScreen( inWorld->x, inWorld->y );
}

int Camera::getHeight() const
{
	return height;
}

void Camera::setHeight(int height)
{
	this->height = height;
}

int Camera::getWidth() const
{
	return width;
}

void Camera::setWidth(int width)
{
	this->width = width;
}

int Camera::getXWorld() const
{
	return xWorld;
}

void Camera::setXWorld(int world)
{
	xWorld = world;
}

int Camera::getYWorld() const
{
	return yWorld;
}

void Camera::setYWorld(int world)
{
	yWorld = world;
}

void Camera::setPosWorld(int x, int y)
{
	setXWorld(x);
	setYWorld(y);
}

void Camera::setPosWorld(SDL_Point point)
{
	setPosWorld( point.x, point.y );
}

SDL_Point Camera::getPosWorld() const
{
	return SDL_Point({xWorld, yWorld});
}

void Camera::setSize(int w, int h)
{
	setWidth( w );
	setHeight( h );
}

SDL_Point Camera::ScreenToWorld(int x, int y)
{
	SDL_Point newPos;
	newPos.x = x + getXWorld();
	newPos.y = y + getYWorld();
	return newPos;
}

SDL_Point Camera::WorldToScreen(int x, int y)
{
	SDL_Point newPos;
	newPos.x = x - getXWorld();
	newPos.y = y - getYWorld();

	return newPos;
}



SDL_Rect Camera::getRect() const
{
    return SDL_Rect({xWorld, yWorld, width, height});
}

SDL_Rect Camera::cameraCulling(const SDL_Rect *src)
{
    SDL_Rect some;
    SDL_Rect cameraRect = getRect();
    SDL_IntersectRect(src, &cameraRect, &some);
   // some.x -=some.w;
   // some.y -=some.h;
    if (some.x >= getXWorld())
     some.x -= getXWorld();
    if (some.y >= getYWorld())
        some.y -= getYWorld();
    return some;
}
