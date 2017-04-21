#pragma once
#include "MobAbility.h"

class MobAbilityArson: public MobAbility
{
public:
    MobAbilityArson();
    virtual ~MobAbilityArson();

    // AbilityModel interface
public:

    virtual bool onReady(double timestep) override;
    virtual bool onWorking(double timestep) override;
    virtual bool onCooldown(double timestep) override;



    // MobAbility interface
public:
    virtual bool isTargetable() override;

    // MobAbility interface
public:
    virtual bool canTrigger(std::shared_ptr<SceneObject>, AIMobStates aistate) override;
private:
    std::shared_ptr<EffectModel> arsonEffect;
    double counter = 0.0;

};


