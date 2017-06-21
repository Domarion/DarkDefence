#pragma once

#include "MobAbility.h"
#include "../AbilityAnims/AbilityAnimObject.hpp"

class MobAbilitySprint : public MobAbility
{
public:

    // AbilityModel interface
    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;
    bool onCooldown(double timestep) override;

    // MobAbility interface
    bool canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate) override;
private:
    std::shared_ptr<AbilityAnimObject> toSpawn;
};

