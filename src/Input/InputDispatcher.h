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
#include <memory>

class InputDispatcher
{
public:
    InputDispatcher();
    ~InputDispatcher() = default;

    void sendEvent(const SDL_Event &inputEvent);
    void addHandler(std::shared_ptr<InputHandler>);
    void removeHandler(std::shared_ptr<InputHandler>);
	void clearHandlers();

private:
    void sendEventTouch(const SDL_Event &inputEvent);
    void sendEventMouse(const SDL_Event &inputEvent);
    uint32_t previousEventType;
    std::vector<std::shared_ptr<InputHandler>> handlers;
};
