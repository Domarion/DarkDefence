#include "MagicWheat.h"

MagicWheat::MagicWheat(Enums::ResourceTypes rType)
    :resType(rType)
{
}

void MagicWheat::init(std::shared_ptr<Scene> /*scenePtr*/, std::shared_ptr<ManaGlobal> /*aManaModel*/)
{
    amount = 5;
    currentTime = period = 3000;
}

void MagicWheat::update(double timestep)
{
    if (currentTime <= 0.0)
    {
        currentTime = period;
        GameModel::getInstance()->getResourcesModel()->addResource(static_cast<int>(resType), amount);
    }
    else
        currentTime -= timestep;
}
