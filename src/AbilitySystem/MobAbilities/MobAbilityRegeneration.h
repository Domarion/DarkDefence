#pragma once
#include "MobAbility.h"

class MobAbilityRegeneration: public MobAbility
{
public:

    MobAbilityRegeneration() = default;

    // AbilityModel interface
    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;
    bool onCooldown(double timestep) override;

    // MobAbility interface
    bool canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate) override;

private:

    double counter = 0.0;
};
