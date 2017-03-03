#pragma once
#include "MobAbility.h"

class MobCloudTowerAbility: public MobAbility
{

    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

    // AbilityModel interface
public:
    MobCloudTowerAbility(std::shared_ptr<ManaGlobal> aManaModel = nullptr);
    virtual ~MobCloudTowerAbility() = default;
    virtual bool onReady(double timestep) override;

    virtual bool onWorking(double timestep) override;
    virtual bool onCooldown(double timestep) override;

    // MobAbility interface
public:
    virtual bool canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate) override;
    SceneObjectList affectedMobs;
    std::shared_ptr<EffectModel> stunEffect;

private:
    void releaseDamage(std::shared_ptr<SceneObject> aTarget);

    // AbilityModel interface
public:
    virtual void init(std::shared_ptr<Scene> scenePtr) override;
};
