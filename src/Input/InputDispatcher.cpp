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
    {
        handlers.erase(iter);
    }
}

void InputDispatcher::clearHandlers()
{
    handlers.clear();
}

void InputDispatcher::sendEventTouch(const SDL_Event& inputEvent)
{

    Position touchPosition
    {
        static_cast<int>(inputEvent.tfinger.x * mSize.width),
        static_cast<int>(inputEvent.tfinger.y * mSize.height)
    };

    if (inputEvent.type == SDL_FINGERUP)
    {
        for (auto& handler : handlers)
        {
            if (handler && handler->onClick(touchPosition))
            {
                break;
            }
        }

        return;
    }

    if (inputEvent.type == SDL_FINGERMOTION && previousEventType == SDL_FINGERDOWN)
    {
        Position diffPosition
        {
            static_cast<int>(inputEvent.tfinger.dx * mSize.width),
            static_cast<int>(inputEvent.tfinger.dy * mSize.height)
        };

        std:: cout << "Touch Diff = " << diffPosition << std::endl;

        for (auto& handler : handlers)
        {
            bool canDrag = handler && handler->canDrag() && handler->containsPoint(touchPosition);
            if (canDrag && handler->onDrag(diffPosition))
            {
                break;
            }
        }
    }
}

void InputDispatcher::sendEventMouse(const SDL_Event& inputEvent)
{
    Position mousePosition;
    SDL_GetMouseState(&(mousePosition.x), &(mousePosition.y));

    if (inputEvent.type == SDL_MOUSEBUTTONUP || inputEvent.type == SDL_MOUSEBUTTONDOWN)
    {
        if (inputEvent.type == SDL_MOUSEBUTTONUP)
        {
            for (auto& handler : handlers)
            {
                if (handler && handler->onClick(mousePosition))
                {
                    break;
                }
            }
        }

        return;
    }

    if (inputEvent.type == SDL_MOUSEMOTION && previousEventType == SDL_MOUSEBUTTONDOWN)
    {
        Position diffPosition
        {
            static_cast<int>(inputEvent.motion.xrel),
            static_cast<int>(inputEvent.motion.yrel)
        };

        std:: cout << "Mouse Diff = " << diffPosition << std::endl;

        for (auto& handler : handlers)
        {
            bool canDrag = handler && handler->canDrag() && handler->containsPoint(mousePosition);
            if (canDrag && handler->onDrag(diffPosition))
            {
                break;
            }
        }
    }
}
