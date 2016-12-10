#pragma once
#include "MobAbility.h"

class MobAbilityFog: public MobAbility
{
public:
    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

    MobAbilityFog();
    virtual ~MobAbilityFog() = default;
private:

    // AbilityModel interface
public:
    virtual bool onReady(double) override;
    virtual bool onWorking(double timestep) override;
    virtual bool onCooldown(double timestep) override;

    // MobAbility interface
public:
    virtual bool canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate) override;
private:
    SceneObjectList affectedMobs;
    std::shared_ptr<EffectModel> fogEffect;

};
