#include "SteelShield.h"
#include "../../Scenes/GameScene.h"

SteelShield::SteelShield()
{

}

SteelShield::~SteelShield()
{

}

void SteelShield::init(std::shared_ptr<Scene> scenePtr)
{
    ManaGlobal* manamodel = GameModel::getInstance()->getManaModel();
    int regen = manamodel->getRegenValue() - 1;
    manamodel->setRegenValue(regen);

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
