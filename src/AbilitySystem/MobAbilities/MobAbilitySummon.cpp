#include "MobAbilitySummon.h"
#include "Scenes/GameScene.h"

MobAbilitySummon::MobAbilitySummon()
    : MobAbility()
{
    currentCooldownTime = cooldownTime = 10000;
}

bool MobAbilitySummon::onReady(double /*timestep*/)
{
    abilityState = target == nullptr? Enums::AbilityStates::asNotAvaliable : Enums::AbilityStates::asWorking;

    return true;
}

bool MobAbilitySummon::onWorking(double /*timestep*/)
{
    if (target != nullptr)
    {
        auto gameScenePtr = std::static_pointer_cast<GameScene>(parentScenePtr);
        if (gameScenePtr != nullptr)
        {
            const size_t spawnCount = 5;
            for (size_t counter = 0; counter < spawnCount; ++counter)
            {
                gameScenePtr->spawningCallBack(
                    "Diversant",
                    target->getPosition(),
                    target->getSprite()->getDrawPriority() + counter + 1);
            }
        }

        abilityState = Enums::AbilityStates::asOnCooldown;
    }
    else
    {
        abilityState = Enums::AbilityStates::asNotAvaliable;
    }
    return true;
}

bool MobAbilitySummon::canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate)
{
    if (aistate == AIMobStates::aiMOVE && targ != nullptr && targ->getTag() == "Monster")
    {
        MobAbility::setTarget(targ);
        return true;
    }

    return false;
}

bool MobAbilitySummon::onCooldown(double timestep)
{
    if (currentCooldownTime <= 0)
    {
        currentCooldownTime = cooldownTime;
        abilityState = Enums::AbilityStates::asNotAvaliable;
    }
    else
        currentCooldownTime -= timestep;

    return true;
}
