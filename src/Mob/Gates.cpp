/*
 * Gates.cpp
 *
 *  Created on: 25 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "Gates.h"

Gates::Gates()
:SceneObject(),model(new DestructibleObject()), effectReceiver(new DestructibleObjectEffectReceiver())
{
	// TODO Auto-generated constructor stub
    effectReceiver->init(model);
}

Gates::~Gates()
{
    delete effectReceiver;
	delete model;
	// TODO Auto-generated destructor stub
}

DestructibleObject* Gates::getModel()
{
	return model;
}

void Gates::setModel(DestructibleObject* newModel)
{
    model = newModel;
    effectReceiver->init(model);

}

EffectReceiver* Gates::getEffectReceiver() const
{
    return effectReceiver;
}

DestructibleObject* Gates::getDestructibleObject()
{
    return model;
}

bool Gates::update(double timestep)
{
    SceneObject::update(timestep);
    if (!model->IsAlive())
    {
      // if (parentScenePtr != nullptr)
        //parentScenePtr->destroyObject(this);
       return false;
    }
    return true;
}
