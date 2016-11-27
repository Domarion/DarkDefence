/*
 * InputHandler.h
 *
 *  Created on: 2 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <SDL2/SDL_rect.h>
#include "../GraphicsSystem/newSystem/UtilityStructs.h"
class InputHandler
{
public:
	InputHandler();
	virtual ~InputHandler();
    virtual bool onClick(Position point) = 0;
	virtual bool canDrag() const;
    virtual bool onDrag(int);
    virtual bool containsPoint(int, int) const;
    //virtual bool canWorkWithGamePause() const;
};

