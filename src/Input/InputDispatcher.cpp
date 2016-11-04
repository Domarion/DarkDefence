/*
 * InputDispatcher.cpp
 *
 *  Created on: 2 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "InputDispatcher.h"
#include <iostream>
#include <algorithm>
InputDispatcher* InputDispatcher::instance_ = nullptr;

InputDispatcher::InputDispatcher()
:previousEventType(0)
{
	// TODO Auto-generated constructor stub

}

InputDispatcher* InputDispatcher::getInstance()
{
	if (instance_ == nullptr)
		instance_ = new InputDispatcher();

	return instance_;
}

InputDispatcher::~InputDispatcher()
{
	// TODO Auto-generated destructor stub
}

void InputDispatcher::sendEvent(SDL_Event* inputEvent)//TODO:: Wrong Logic
{
	if (inputEvent->type == SDL_MOUSEBUTTONUP || inputEvent->type == SDL_MOUSEBUTTONDOWN)
	{

		SDL_Point point;
		SDL_GetMouseState(&(point.x), &(point.y));

		if (inputEvent->type == SDL_MOUSEBUTTONUP)
		for(unsigned int i = 0; i != handlers.size(); ++i)
		{
			if(handlers[i]->onClick(&point))
				break;
		}
	}
	else
		if (inputEvent->type == SDL_MOUSEMOTION && (previousEventType == SDL_MOUSEBUTTONDOWN) )
		{

			int yDiff = - inputEvent->motion.yrel;
			std:: cout << "Mouse yDiff = " << yDiff << std::endl;
			for(unsigned int i = 0; i != handlers.size(); ++i)
			{
				if(handlers[i]->canDrag() && handlers[i]->containsPoint(inputEvent->motion.x, inputEvent->motion.y))
				{

                    if (handlers[i]->onDrag(yDiff))
                        break;
				}
			}
		}

	previousEventType = inputEvent->type;
}

void InputDispatcher::addHandler(InputHandler* handler)
{
	handlers.push_back(handler);
}

void InputDispatcher::removeHandler(InputHandler* handler)
{

     std::vector<InputHandler*>::iterator it = std::find(handlers.begin(), handlers.end(), handler);


    if (it != handlers.end())
        for(; it != handlers.end(); ++it)
        {
                *it = *(it + 1);
        }
          //  handlers[i] = handlers[i + 1];

    handlers.pop_back();
	//TODO:stub
}

void InputDispatcher::clearHandlers()
{
	handlers.clear();
}
