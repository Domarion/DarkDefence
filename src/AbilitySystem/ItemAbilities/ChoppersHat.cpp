#include "ChoppersHat.h"

ChoppersHat::ChoppersHat(Enums::ResourceTypes rType)
    :resType(rType)
{

}

ChoppersHat::~ChoppersHat()
{

}

void ChoppersHat::init(std::shared_ptr<Scene> scenePtr)
{
   // resType = Enums::ResourceTypes::WOOD;
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
        GameModel::getInstance()->getResourcesModel()->addResource(static_cast<int>(resType), amount);
    }
    else
        currentTime -= timestep;
}
