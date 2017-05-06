#include "CaftanOfGold.h"

CaftanOfGold::CaftanOfGold()
{

}

CaftanOfGold::~CaftanOfGold()
{

}

void CaftanOfGold::init(std::shared_ptr<Scene>, std::shared_ptr<ManaGlobal> aManaModel)
{
    pointsAmount = 2;
    currentTime = period = 3000;

    int newRegenValue = aManaModel->getRegenValue() - 1;
    aManaModel->setRegenValue(newRegenValue);
}

void CaftanOfGold::update(double timestep)
{
    if (currentTime <= 0.0)
    {
        currentTime = period;
        GameModel::getInstance()->addPoints(pointsAmount);
    }
    else
        currentTime -= timestep;
}
