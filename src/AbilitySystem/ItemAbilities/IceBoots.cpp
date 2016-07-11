#include "IceBoots.h"
#include "../../Scenes/GameScene.h"

IceBoots::IceBoots()
{

}

IceBoots::~IceBoots()
{

}

void IceBoots::init(Scene * const scenePtr)
{

    GameScene* gameScenePtr = dynamic_cast<GameScene*>(scenePtr);
    if (gameScenePtr == nullptr)
        return;
    AbilityModel* magicStone = gameScenePtr->getAbilityModelWithName("SnowStorm");
    if (magicStone != nullptr)
    {
        int manaCost = static_cast<int>( 0.5 * magicStone->getManaCost());
        magicStone->setManaCost(manaCost);
        double workTime = magicStone->getWorkTime() *2;
        magicStone->setWorkTime(workTime);
    }
}
