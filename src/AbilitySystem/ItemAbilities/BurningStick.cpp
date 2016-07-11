#include "BurningStick.h"

BurningStick::BurningStick()
{

}

BurningStick::~BurningStick()
{

}


void BurningStick::init(Scene* const scenePtr)
{
    amount = 2;
    currentTime = period = 3000;

    ManaGlobal* manaModelPtr = GameModel::getInstance()->getManaModel();

    int newRegenValue = manaModelPtr->getRegenValue() + 5;
    manaModelPtr->setRegenValue(newRegenValue);

}

void BurningStick::update(double timestep)
{
    if (currentTime <= 0.0)
    {
        currentTime = period;
        GameModel::getInstance()->getResourcesModel()->removeResource(Enums::ResourceTypes::WOOD, amount);
    }
    else
        currentTime -= timestep;
}

