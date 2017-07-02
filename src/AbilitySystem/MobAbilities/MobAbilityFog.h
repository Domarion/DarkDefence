#pragma once

#include "MobAbility.h"

class MobAbilityFog: public MobAbility
{
public:
    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

    MobAbilityFog();

    // AbilityModel interface
    bool onReady(double) override;
    bool onWorking(double timestep) override;
    bool onCooldown(double timestep) override;

    // MobAbility interface
    bool canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate) override;

private:
    std::shared_ptr<EffectModel> fogEffect;
    SceneObjectList affectedMobs;

};
