/*
 * InputHandler.h
 *
 *  Created on: 2 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <SDL_rect.h>

class InputHandler
{
public:
	InputHandler();
	virtual ~InputHandler();
	virtual bool onClick(SDL_Point* point) = 0;
	virtual bool canDrag() const;
    virtual bool onDrag(int);
    virtual bool containsPoint(int, int) const;
    //virtual bool canWorkWithGamePause() const;
};

