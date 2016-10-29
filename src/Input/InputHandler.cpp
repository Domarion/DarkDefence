/*
 * InputHandler.cpp
 *
 *  Created on: 2 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "InputHandler.h"

InputHandler::InputHandler()
{
	// TODO Auto-generated constructor stub

}

InputHandler::~InputHandler()
{
	// TODO Auto-generated destructor stub
}

bool InputHandler::onDrag(int /*direction*/)
{
	return false;
}

bool InputHandler::canDrag() const
{
	return false;
}

bool InputHandler::containsPoint(int /*x*/, int /*y*/) const
{
    return false;
}

