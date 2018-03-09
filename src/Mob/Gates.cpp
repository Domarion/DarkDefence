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

void Gates::setModel(const std::shared_ptr<DestructibleObject>& aNewModel)
{
    model = aNewModel;
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
    if (!model->IsAlive())
    {
       return false;
    }

    return SceneObject::update(timestep);
}
