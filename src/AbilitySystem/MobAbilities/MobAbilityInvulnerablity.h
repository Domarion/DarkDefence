#pragma once

#include "MobAbility.h"

class MobAbilityInvulnerablity : public MobAbility
{
public:

    // AbilityModel interface
    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;
    bool onCooldown(double timestep) override;

    // MobAbility interface
    bool canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate) override;
private:
    const int protectionModifier = 9999;
};

