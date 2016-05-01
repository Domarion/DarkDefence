/*
 * Camera.h
 *
 *  Created on: 24 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <SDL2/SDL.h>
class Camera
{
public:
	Camera(	int xWorldPos, int yWorldPos, int aWidth, int aHeight );
	virtual ~Camera();
	SDL_Point ScreenToWorld(SDL_Point* onScreen);
	SDL_Point WorldToScreen(SDL_Point* inWorld);
	SDL_Point ScreenToWorld(int x, int y);
	SDL_Point WorldToScreen(int x, int y);
	int getHeight() const;
	void setHeight(int height);
	int getWidth() const;
	void setWidth(int width);
	int getXWorld() const;
	void setXWorld(int world);
	int getYWorld() const;
	void setYWorld(int world);
	void setPosWorld(int x, int y);
	void setPosWorld(SDL_Point point);
	SDL_Point getPosWorld() const;
	void setSize(int w, int h);
	SDL_Rect getRect() const;
    SDL_Rect cameraCulling(const SDL_Rect *src);
private:
	int xWorld, yWorld;
	int width, height;
};

