#include "HelmOfGold.h"

HelmOfGold::HelmOfGold()
{

}

HelmOfGold::~HelmOfGold()
{

}

void HelmOfGold::init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel)
{
    goldAmount = 1;
    currentTime = period = 3000;

    int newMaxMana = aManaModel->getLimit() - 30;
    aManaModel->setLimit(newMaxMana);

}

void HelmOfGold::update(double timestep)
{
    if (currentTime <= 0.0)
    {
        currentTime = period;
        //GameModel::getInstance()->getResourcesModel()->addResource(Enums::ResourceTypes::GOLD, goldAmount);
    }
    else
        currentTime -= timestep;
}
