#pragma once
#include "MobAbility.h"

class MobAbilityArson: public MobAbility
{
public:
    MobAbilityArson();
    virtual ~MobAbilityArson();

    // AbilityModel interface
public:
    virtual void init(Scene * const scenePtr) override;
    virtual bool onReady(double timestep) override;
    virtual bool onWorking(double timestep) override;
    virtual bool onCooldown(double timestep) override;
private:
    DestructibleObject* target;
};


