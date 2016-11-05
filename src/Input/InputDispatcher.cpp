/*
 * InputDispatcher.cpp
 *
 *  Created on: 2 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "InputDispatcher.h"
#include <iostream>
#include <algorithm>

InputDispatcher::InputDispatcher()
:previousEventType(0)
{
}


void InputDispatcher::sendEvent(const SDL_Event& inputEvent)//TODO:: Wrong Logic
{
    if (inputEvent.type == SDL_MOUSEBUTTONUP || inputEvent.type == SDL_MOUSEBUTTONDOWN)
	{

		SDL_Point point;
		SDL_GetMouseState(&(point.x), &(point.y));

        if (inputEvent.type == SDL_MOUSEBUTTONUP)
		for(unsigned int i = 0; i != handlers.size(); ++i)
		{
			if(handlers[i]->onClick(&point))
				break;
		}
	}
	else
        if (inputEvent.type == SDL_MOUSEMOTION && (previousEventType == SDL_MOUSEBUTTONDOWN) )
		{

            int yDiff = - inputEvent.motion.yrel;
			std:: cout << "Mouse yDiff = " << yDiff << std::endl;
			for(unsigned int i = 0; i != handlers.size(); ++i)
			{
                if(handlers[i]->canDrag() && handlers[i]->containsPoint(inputEvent.motion.x, inputEvent.motion.y))
				{

                    if (handlers[i]->onDrag(yDiff))
                        break;
				}
			}
		}

    previousEventType = inputEvent.type;
}

void InputDispatcher::addHandler(std::shared_ptr<InputHandler> handler)
{
	handlers.push_back(handler);
}

void InputDispatcher::removeHandler(std::shared_ptr<InputHandler> handler)
{
    auto iter = std::find(handlers.begin(), handlers.end(), handler);

    if (iter != handlers.end())
        handlers.erase(iter);
}

void InputDispatcher::clearHandlers()
{
	handlers.clear();
}
