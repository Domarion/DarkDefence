#pragma once

#include "MobAbility.h"

class MobEarthTowerAbility: public MobAbility
{
public:

    MobEarthTowerAbility();

    // AbilityModel interface
    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;
    bool onCooldown(double timestep) override;

    // MobAbility interface
    bool canTrigger(std::shared_ptr<SceneObject>, Enums::AIMobStates) override;

private:

    std::shared_ptr<SceneObject> gates;
    std::shared_ptr<EffectModel> effect;
};
