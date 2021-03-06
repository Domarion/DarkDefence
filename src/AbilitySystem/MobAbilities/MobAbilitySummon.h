#pragma once

#include "MobAbility.h"

class MobAbilitySummon : public MobAbility
{
public:
    MobAbilitySummon();
    // AbilityModel interface
    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;
    bool onCooldown(double timestep) override;

    // MobAbility interface
    bool canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate) override;
};
