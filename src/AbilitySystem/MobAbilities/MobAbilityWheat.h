#pragma once
#include "MobAbility.h"

class MobAbilityWheat: public MobAbility
{
public:
    MobAbilityWheat() = default;
    virtual ~MobAbilityWheat() = default;


    // AbilityModel interface
public:
    virtual bool onReady(double) override;
    virtual bool onWorking(double timestep) override;

    // MobAbility interface
public:
    virtual bool canTrigger(std::shared_ptr<SceneObject>, Enums::AIMobStates aistate) override;

    // AbilityModel interface
public:
    virtual bool onCooldown(double) override;
};
