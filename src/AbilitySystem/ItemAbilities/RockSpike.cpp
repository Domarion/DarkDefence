#include "RockSpike.h"
#include "../AbilityPrick.h"
#include "../../Scenes/GameScene.h"

RockSpike::RockSpike()
{

}

RockSpike::~RockSpike()
{

}

void RockSpike::init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> /*aManaModel*/)
{
    amount = 3;
    currentTime = period = 3000;
    auto gameScenePtr = std::dynamic_pointer_cast<GameScene>(scenePtr);
    if (gameScenePtr == nullptr)
        return;
    std::shared_ptr<AbilityPrick> prick = std::dynamic_pointer_cast<AbilityPrick>(gameScenePtr->getAbilityModelWithName("Prick"));
    if (prick != nullptr)
    {
        int dmg = static_cast<int>( 1.5 * prick->getDamage());
        prick->setDamage(dmg);
        double cooldown = static_cast<int>( prick->getCooldownTime() * 0.5);
        prick->setCooldownTime(cooldown);
    }
}


void RockSpike::update(double timestep)
{

    if (currentTime <= 0.0)
    {
        currentTime = period;
        GameModel::getInstance()->getResourcesModel()->addResource(static_cast<int>(Enums::ResourceTypes::STONE), amount);
    }
    else
        currentTime -= timestep;

}
