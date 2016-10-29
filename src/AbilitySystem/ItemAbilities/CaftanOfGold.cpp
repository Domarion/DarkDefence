#include "CaftanOfGold.h"

CaftanOfGold::CaftanOfGold()
{

}

CaftanOfGold::~CaftanOfGold()
{

}

void CaftanOfGold::init(std::shared_ptr<Scene> scenePtr)
{
    goldAmount = 2;
    currentTime = period = 3000;

    ManaGlobal* manaModelPtr = GameModel::getInstance()->getManaModel();

    int newRegenValue = manaModelPtr->getRegenValue() - 1;
    manaModelPtr->setRegenValue(newRegenValue);

}

void CaftanOfGold::update(double timestep)
{
    if (currentTime <= 0.0)
    {
        currentTime = period;
        //GameModel::getInstance()->getResourcesModel()->addResource(Enums::ResourceTypes::GOLD, goldAmount);
    }
    else
        currentTime -= timestep;
}
