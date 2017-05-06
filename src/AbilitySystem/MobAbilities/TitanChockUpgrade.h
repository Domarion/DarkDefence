#pragma once
#include "MobAbility.h"

class TitanChockUpgrade: public MobAbility
{
    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

public:
    TitanChockUpgrade(std::shared_ptr<ManaGlobal> aManaModel = nullptr);
    virtual ~TitanChockUpgrade() = default;
    virtual bool onReady(double timestep) override;

    virtual bool onWorking(double timestep) override;
    virtual bool onCooldown(double timestep) override;

public:
    virtual bool canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate) override;
    virtual void init(std::shared_ptr<Scene> scenePtr) override;

private:
    void releaseDamage(std::shared_ptr<SceneObject> aTarget);
    SceneObjectList affectedMobs;
    std::shared_ptr<EffectModel> stunEffect;
};
