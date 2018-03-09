#pragma once

#include "MobAbility.h"
#include "../AbilityAnims/AbilityMultitargetObject.hpp"

class MobCloudTowerAbility: public MobAbility
{
public:

    MobCloudTowerAbility(std::shared_ptr<ManaGlobal> aManaModel = nullptr);

    // AbilityModel interface
    void init(std::shared_ptr<Scene> scenePtr) override;
    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;
    bool onCooldown(double timestep) override;

    // MobAbility interface
    bool canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate) override;
private:
    void ChainLightingHandler(std::shared_ptr<SceneObject> aTarget);
    void releaseDamage(std::shared_ptr<SceneObject> aTarget);

    std::shared_ptr<EffectModel> stunEffect;
    std::shared_ptr<AbilityMultitargetObject> aBouncingArrowObject;
};
