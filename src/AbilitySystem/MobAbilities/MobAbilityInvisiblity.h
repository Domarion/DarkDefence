#pragma once
#include "MobAbility.h"
class MobAbilityInvisiblity: public MobAbility
{
public:
    MobAbilityInvisiblity();
    virtual ~MobAbilityInvisiblity();

    // AbilityModel interface
public:
    virtual bool onReady(double timestep) override;
    virtual bool onWorking(double timestep) override;
    virtual bool onCooldown(double timestep) override;


    // MobAbility interface
public:
    virtual bool canTrigger(SceneObject *targ, Enums::AIMobStates aistate) override;
};
