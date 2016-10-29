#pragma once
#include "MobAbility.h"

class MobAbilityRegeneration: public MobAbility
{
public:
    MobAbilityRegeneration();
    virtual ~MobAbilityRegeneration();

    // AbilityModel interface
public:
    virtual bool onReady(double timestep) override;
    virtual bool onWorking(double timestep) override;
    virtual bool onCooldown(double timestep) override;


    // MobAbility interface
public:
    virtual bool canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate) override;
};
