#include "SteelShield.h"

SteelShield::SteelShield()
{

}

SteelShield::~SteelShield()
{

}

void SteelShield::init(GameScene * const scenePtr)
{
    ManaGlobal* manamodel = GameModel::getInstance()->getManaModel();
    int regen = manamodel->getRegenValue() - 1;
    manamodel->setRegenValue(regen);

    AbilityModel* magicStone = scenePtr->getAbilityModelWithName("MagicStones");
    if (magicStone != nullptr)
    {
        double workTime = magicStone->getWorkTime() *1.4;
        magicStone->setWorkTime(workTime);
    }
}
