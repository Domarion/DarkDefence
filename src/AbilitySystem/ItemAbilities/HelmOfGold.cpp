#include "HelmOfGold.h"

HelmOfGold::HelmOfGold()
{

}

HelmOfGold::~HelmOfGold()
{

}

void HelmOfGold::init(Scene* const scenePtr)
{
    goldAmount = 1;
    currentTime = period = 3000;

    ManaGlobal* manaModelPtr = GameModel::getInstance()->getManaModel();

    int newMaxMana = manaModelPtr->getLimit() - 30;
    manaModelPtr->setLimit(newMaxMana);

}

void HelmOfGold::update(double timestep)
{
    if (currentTime <= 0.0)
    {
        currentTime = period;
        GameModel::getInstance()->getResourcesModel()->addResource(Enums::ResourceTypes::GOLD, goldAmount);
    }
    else
        currentTime -= timestep;
}
