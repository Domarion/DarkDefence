#pragma once
#include "MobAbility.h"

class MobMageTowerAbility: public MobAbility
{
public:
    MobMageTowerAbility() = default;
    virtual ~MobMageTowerAbility() = default;

    // AbilityModel interface
public:
    virtual bool onReady(double timestep) override;
    virtual bool onWorking(double timestep) override;
    virtual bool onCooldown(double timestep) override;

    // MobAbility interface
public:
    virtual bool canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate) override;
};
