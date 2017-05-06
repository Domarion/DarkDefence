#include "MerchantsHat.h"

void MerchantsHat::init(std::shared_ptr<Scene> /*scenePtr*/, std::shared_ptr<ManaGlobal> aManaModel)
{
    pointsAmount = 1;
    currentTime = period = 3000;

    int newMaxMana = aManaModel->getLimit() - 30;
    aManaModel->setLimit(newMaxMana);
}

void MerchantsHat::update(double timestep)
{
    if (currentTime <= 0.0)
    {
        currentTime = period;
        GameModel::getInstance()->addPoints(pointsAmount);
    }
    else
        currentTime -= timestep;
}
