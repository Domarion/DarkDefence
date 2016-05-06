#include "Mine.h"

Mine::Mine()
    :model(nullptr)
{

}

void Mine::init()
{

}

bool Mine::update(double timestep)
{

    if (model != nullptr)
        model->produce(timestep);

    return true;
}

void Mine::finalize()
{

}

DestructibleObject *Mine::getDestructibleObject()
{
    return model;
}

EffectReceiver *Mine::getEffectReceiver() const
{

}

MineModel * const Mine::getMineModel()
{
    return model;
}

void Mine::setMineModel(MineModel * const newModel)
{
   model = newModel;
}
