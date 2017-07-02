#include "MobAbilityFog.h"
#include "../AbilityAnims/AbilityAnimObject.hpp"

MobAbilityFog::MobAbilityFog()
: MobAbility()
, fogEffect(std::make_shared<EffectModel>())
{
    pair<string, double> rt = std::make_pair("ReloadTime", +5.0e+6);
    fogEffect->addMiniEffect(rt);
}

bool MobAbilityFog::onReady(double)
{
    if (parentScenePtr != nullptr)
    {
        affectedMobs = parentScenePtr->findObjectsByTag("Tower");
        if (affectedMobs != nullptr)
        {
            for(auto& affectedMob : *affectedMobs)
            {
                if (affectedMob != nullptr)
                {
                    auto effectReceiver = affectedMob->getEffectReceiver();
                    if (effectReceiver != nullptr)
                    {
                        effectReceiver->applyEffect(fogEffect);

                        auto toSpawn = Make_AbilityAnimObject(
                            "MobAbilities/MobAbilityFog", Size(100, 100), workTime, parentScenePtr->getRenderer());

                        if (toSpawn == nullptr)
                            return false;

                        auto position = affectedMob->getRealPosition();
                        parentScenePtr->spawnObject(position.x, position.y, toSpawn);

                    }
                }
            }
            abilityState = Enums::AbilityStates::asWorking;
            currentWorkTime = workTime;
        }
    }

    return true;
}

bool MobAbilityFog::onWorking(double timestep)
{
    if (currentWorkTime <= 0)
    {
        abilityState = Enums::AbilityStates::asOnCooldown;
        currentCooldownTime = cooldownTime;

        if (affectedMobs == nullptr)
            return true;

        for(auto& affectedMob : *affectedMobs)
        {
            if (affectedMob != nullptr)
            {
                auto effectReceiver = affectedMob->getEffectReceiver();
                if (effectReceiver != nullptr)
                {
                    effectReceiver->cancelEffect(fogEffect);
                }
            }
        }
        affectedMobs.reset();
    }
    else
        currentCooldownTime -= timestep;

    return true;
}

bool MobAbilityFog::onCooldown(double timestep)
{
    if (currentCooldownTime <= 0)
    {
        abilityState = Enums::AbilityStates::asNotAvaliable;
    }
    else
        currentCooldownTime -= timestep;

    return true;
}

bool MobAbilityFog::canTrigger(std::shared_ptr<SceneObject>, Enums::AIMobStates aistate)
{
    return abilityState == Enums::AbilityStates::asNotAvaliable && aistate != Enums::AIMobStates::aiSELECT;
}
