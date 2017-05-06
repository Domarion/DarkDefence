#include "MonolithShard.h"
#include "../../Scenes/GameScene.h"

void MonolithShard::init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel)
{


    int regen = aManaModel->getRegenValue() + 2;
    aManaModel->setRegenValue(regen);

    auto gameScenePtr = std::dynamic_pointer_cast<GameScene>(scenePtr);
    if (gameScenePtr == nullptr)
        return;

    gatesDestructible = gameScenePtr->findObjectByTag("Gates")->getDestructibleObject();

    auto magicStone = gameScenePtr->getAbilityModelWithName("MagicStones");
    if (magicStone != nullptr)
    {
        double cooldown = magicStone->getCooldownTime() * 0.5;
        magicStone->setCooldownTime(cooldown);

        int cost = magicStone->getManaCost()/2;
        magicStone->setManaCost(cost);

    }
}

void MonolithShard::update(double timestep)
{
    if (gatesDestructible == nullptr)
        return;

    if (currentTime <= 0.0)
    {
        currentTime = period;
        int amount = static_cast<int>(gatesDestructible->getMaximumHealth()* 0.05);
        gatesDestructible->addHealth(amount);
    }
    else
        currentTime -= timestep;
}

