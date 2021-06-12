#include "InputHandler.h"

bool InputHandler::onDrag(Position /*aDirection*/)
{
    return false;
}

bool InputHandler::canDrag() const
{
    return false;
}

bool InputHandler::containsPoint(Position /*aPosition*/) const
{
    return false;
}

bool InputHandler::canConsumeInput() const
{
    return false;
}
