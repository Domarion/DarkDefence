#include "SteelShield.h"
#include "../../Scenes/GameScene.h"

SteelShield::SteelShield()
{

}

SteelShield::~SteelShield()
{

}

void SteelShield::init(Scene * const scenePtr)
{
    ManaGlobal* manamodel = GameModel::getInstance()->getManaModel();
    int regen = manamodel->getRegenValue() - 1;
    manamodel->setRegenValue(regen);

    GameScene* gameScenePtr = dynamic_cast<GameScene*>(scenePtr);
    if (gameScenePtr == nullptr)
        return;
    AbilityModel* magicStone = gameScenePtr->getAbilityModelWithName("MagicStones");
    if (magicStone != nullptr)
    {
        double workTime = magicStone->getWorkTime() *1.4;
        magicStone->setWorkTime(workTime);
    }
}
