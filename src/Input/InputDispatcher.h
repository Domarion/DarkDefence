/*
 * InputDispatcher.h
 *
 *  Created on: 2 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <SDL.h>
#include "InputHandler.h"
#include <vector>

class InputDispatcher
{
public:

	static InputDispatcher* getInstance();


	void sendEvent(SDL_Event* inputEvent);
	void addHandler(InputHandler*);
	void removeHandler(InputHandler*);
	void clearHandlers();
protected:

	InputDispatcher();
	~InputDispatcher();

private:

    uint32_t previousEventType;
	std::vector<InputHandler*> handlers;
	static InputDispatcher* instance_;
};
