#pragma once

#include "MobAbility.h"

class MobAbilityWheat: public MobAbility
{
public:

    // AbilityModel interface
    bool onReady(double) override;
    bool onWorking(double timestep) override;
    bool onCooldown(double) override;

    // MobAbility interface
    bool canTrigger(std::shared_ptr<SceneObject>, Enums::AIMobStates aistate) override;
};
