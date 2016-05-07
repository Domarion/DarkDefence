#include "ChoppersHat.h"

ChoppersHat::ChoppersHat()
{

}

ChoppersHat::~ChoppersHat()
{

}

void ChoppersHat::init(GameScene * const scenePtr)
{
    resType = Enums::ResourceTypes::WOOD;
    amount = 2;
    currentTime = period = 3000;
    MineModel* mmodel = GameModel::getInstance()->getMineModelFromListByRes(resType);
    int productionNew = static_cast<int> (mmodel->getProduction() * 1.3);
    mmodel->setProduction(productionNew);
}

void ChoppersHat::update(double timestep)
{
    if (currentTime <= 0.0)
    {
        currentTime = period;
        GameModel::getInstance()->getResourcesModel()->addResource(resType, amount);
    }
    else
        currentTime -= timestep;
}
