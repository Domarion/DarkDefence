/*
 * Gates.cpp
 *
 *  Created on: 25 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "Gates.h"

Gates::Gates()
: SceneObject()
, model(std::make_shared<DestructibleObject>())
, effectReceiver(std::make_shared<DestructibleObjectEffectReceiver>())
{
    effectReceiver->init(model);
}

std::shared_ptr<DestructibleObject> Gates::getModel()
{
	return model;
}

void Gates::setModel(std::shared_ptr<DestructibleObject> newModel)
{
    model = newModel;
    effectReceiver->init(model);

}

std::shared_ptr<EffectReceiver> Gates::getEffectReceiver() const
{
    return effectReceiver;
}

std::shared_ptr<DestructibleObject> Gates::getDestructibleObject() const
{
    return model;
}

bool Gates::update(double timestep)
{
    SceneObject::update(timestep);
    if (!model->IsAlive())
    {
       return false;
    }
    return true;
}
