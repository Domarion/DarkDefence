#include "BurningAxe.h"
#include "../../Scenes/GameScene.h"

void BurningAxe::init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> /*aManaModel*/)
{
    amount = 3;
    currentTime = period = 3000;

    auto gameScenePtr = std::dynamic_pointer_cast<GameScene>(scenePtr);
    if (gameScenePtr == nullptr)
        return;

    auto magicStone = gameScenePtr->getAbilityModelWithName("MagicStones");
    if (magicStone != nullptr)
    {
        double workTime = magicStone->getWorkTime() * 0.5;
        magicStone->setWorkTime(workTime);
    }
}

void BurningAxe::update(double timestep)
{
    if (currentTime <= 0.0)
    {
        currentTime = period;
        GameModel::getInstance()->getResourcesModel()->addResource(
            Enums::toIntegralType(Enums::ResourceTypes::WOOD), amount);
    }
    else
        currentTime -= timestep;
}
