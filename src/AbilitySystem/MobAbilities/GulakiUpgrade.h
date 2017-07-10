#pragma once

#include "MobAbility.h"
#include "../AbilityAnims/AbilityMultitargetObject.hpp"

class GulakiUpgrade: public MobAbility
{
//    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

public:

    GulakiUpgrade(std::shared_ptr<ManaGlobal> aManaModel = nullptr);

    // AbilityModel interface
    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;
    bool onCooldown(double timestep) override;

    // MobAbility interface
    bool canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate) override;

private:
    void ChainLightingHandler(std::shared_ptr<SceneObject> aTarget);
    void releaseDamage(std::shared_ptr<SceneObject> aTarget);
//    SceneObjectList affectedMobs;
    std::shared_ptr<EffectModel> stunEffect;
    std::shared_ptr<AbilityMultitargetObject> aBouncingArrowObject;
};
