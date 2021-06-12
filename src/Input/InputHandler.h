#pragma once

#include <SDL_rect.h>

#include "../GraphicsSystem/newSystem/UtilityStructs.h"

class InputHandler
{
public:
    virtual ~InputHandler() = default;

    virtual bool onClick(Position point) = 0;
    virtual bool canDrag() const;
    virtual bool onDrag(Position);
    virtual bool containsPoint(Position) const;
    virtual bool canConsumeInput() const;
};

