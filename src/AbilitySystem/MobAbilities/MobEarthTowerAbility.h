#pragma once
#include "MobAbility.h"

class MobEarthTowerAbility: public MobAbility
{


    // AbilityModel interface
public:
    MobEarthTowerAbility();
    virtual ~MobEarthTowerAbility() = default;
    virtual bool onReady(double timestep) override;
    virtual bool onWorking(double timestep) override;
    virtual bool onCooldown(double timestep) override;

    // MobAbility interface
public:
    virtual bool canTrigger(std::shared_ptr<SceneObject>, Enums::AIMobStates) override;
    std::shared_ptr<SceneObject> gates;
    std::shared_ptr<EffectModel> effect;
};
