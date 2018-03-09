#include "IceBoots.h"
#include "../../Scenes/GameScene.h"

void IceBoots::init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> /*aManaModel*/)
{
    auto gameScenePtr = std::dynamic_pointer_cast<GameScene>(scenePtr);
    if (gameScenePtr == nullptr)
        return;

    auto magicStone = gameScenePtr->getAbilityModelWithName("SnowStorm");
    if (magicStone != nullptr)
    {
        int manaCost = static_cast<int>( 0.5 * magicStone->getManaCost());
        magicStone->setManaCost(manaCost);
        double workTime = magicStone->getWorkTime() *2;
        magicStone->setWorkTime(workTime);
    }
}
