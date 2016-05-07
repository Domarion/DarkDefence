#include "IceBoots.h"

IceBoots::IceBoots()
{

}

IceBoots::~IceBoots()
{

}

void IceBoots::init(GameScene * const scenePtr)
{
    AbilityModel* magicStone = scenePtr->getAbilityModelWithName("SnowStorm");
    if (magicStone != nullptr)
    {
        int manaCost = static_cast<int>( 0.5 * magicStone->getManaCost());
        magicStone->setManaCost(manaCost);
        double workTime = magicStone->getWorkTime() *2;
        magicStone->setWorkTime(workTime);
    }
}
