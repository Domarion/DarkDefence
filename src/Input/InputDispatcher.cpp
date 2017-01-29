/*
 * InputDispatcher.cpp
 *
 *  Created on: 2 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "InputDispatcher.h"
#include <iostream>
#include <algorithm>

InputDispatcher::InputDispatcher(Size aSize)
: previousEventType(0)
, mSize(aSize)
{
}


void InputDispatcher::sendEvent(const SDL_Event& inputEvent)//TODO:: Wrong Logic
{
    #ifdef __ANDROID__
        sendEventTouch(inputEvent);
    #else
        sendEventMouse(inputEvent);
    #endif

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

void InputDispatcher::sendEventTouch(const SDL_Event &inputEvent)
{

    int x = static_cast<int>(inputEvent.tfinger.x * mSize.width);
    int y = static_cast<int>(inputEvent.tfinger.y * mSize.height);

    if (inputEvent.type == SDL_FINGERUP)
    {

        Position point{x, y};

        for(unsigned int i = 0; i != handlers.size(); ++i)
        {
            if(handlers[i] != nullptr && handlers[i]->onClick(point))
                break;
        }

    }
    else if (inputEvent.type == SDL_FINGERMOTION && (previousEventType == SDL_FINGERDOWN) )
    {
        int yDiff = - static_cast<int>(inputEvent.tfinger.dy * mSize.height);

        std:: cout << "Touch yDiff = " << yDiff << std::endl;
//        if (inputEvent.type == SDL_MOUSEMOTION)
//        {
//           yDiff =- inputEvent.motion.yrel/3;
//        } 

        for(unsigned int i = 0; i != handlers.size(); ++i)
        {
            if(handlers[i] != nullptr && handlers[i]->canDrag() && handlers[i]->containsPoint(x, y))
            {
                if (handlers[i]->onDrag(yDiff))
                    break;
            }
        }
    }
}

void InputDispatcher::sendEventMouse(const SDL_Event &inputEvent)
{
    if (inputEvent.type == SDL_MOUSEBUTTONUP || inputEvent.type == SDL_MOUSEBUTTONDOWN)
    {

        Position point;
        SDL_GetMouseState(&(point.x), &(point.y));

        if (inputEvent.type == SDL_MOUSEBUTTONUP)
        for(unsigned int i = 0; i != handlers.size(); ++i)
        {
            if(handlers[i] != nullptr && handlers[i]->onClick(point))
                break;
        }
    }
    else
        if (inputEvent.type == SDL_MOUSEMOTION && (previousEventType == SDL_MOUSEBUTTONDOWN) )
        {
            Position point;
            SDL_GetMouseState(&(point.x), &(point.y));


            int yDiff = - inputEvent.motion.yrel;
            std:: cout << "Mouse yDiff = " << yDiff << std::endl;
            for(unsigned int i = 0; i != handlers.size(); ++i)
            {
                if(handlers[i] != nullptr && handlers[i]->canDrag() && handlers[i]->containsPoint(point.x, point.y))
                {

                    if (handlers[i]->onDrag(yDiff))
                        break;
                }
            }
        }
}
