#include "SteelShield.h"
#include "../../Scenes/GameScene.h"

void SteelShield::init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel)
{

    int regen = aManaModel->getRegenValue() - 1;
    aManaModel->setRegenValue(regen);

    auto gameScenePtr = std::dynamic_pointer_cast<GameScene>(scenePtr);
    if (gameScenePtr == nullptr)
        return;
    auto magicStone = gameScenePtr->getAbilityModelWithName("MagicStones");
    if (magicStone != nullptr)
    {
        double workTime = magicStone->getWorkTime() *1.4;
        magicStone->setWorkTime(workTime);
    }
}
