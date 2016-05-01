/*
 * Gates.cpp
 *
 *  Created on: 25 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "Gates.h"

Gates::Gates()
:SceneObject(),model(new DestructibleObject())
{
	// TODO Auto-generated constructor stub

}

Gates::~Gates()
{

	delete model;
	// TODO Auto-generated destructor stub
}

DestructibleObject* const Gates::getModel()
{
	return model;
}

void Gates::setModel(DestructibleObject* newModel)
{
	model = newModel;
}

DestructibleObject* Gates::getDestructibleObject()
{
    return model;
}
