#pragma once
#include "MobAbility.h"

class TitanChockMassSlow: public MobAbility
{

    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

    // AbilityModel interface
public:
    TitanChockMassSlow(std::shared_ptr<ManaGlobal> aManaModel = nullptr);
    virtual ~TitanChockMassSlow() = default;
    virtual bool onReady(double timestep) override;

    virtual bool onWorking(double timestep) override;
    virtual bool onCooldown(double timestep) override;

    // MobAbility interface
public:
    virtual bool canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate) override;

private:
    SceneObjectList affectedMobs;
    std::shared_ptr<EffectModel> slowEffect;
};
