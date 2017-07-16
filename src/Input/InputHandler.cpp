/*
 * InputHandler.cpp
 *
 *  Created on: 2 апр. 2016 г.
 *      Author: kostya_hm
 */

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
