#pragma once
#include "AbilityModel.h"
#include "EffectModel.h"
#include "AbilityAnims/AbilityAnimObject.hpp"

class AbilityShrink: public AbilityModel
{
    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

public:
    AbilityShrink(std::shared_ptr<ManaGlobal> aManaModel);
    virtual ~AbilityShrink();

    void init(std::shared_ptr<Scene> scenePtr) override;
    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;
    void setDamagePerSecond(double value);
    double getDamagePerSecond() const;
private:
    double damagePerSecond;
    SceneObjectList affectedMobs;
    std::shared_ptr<AbilityAnimObject> spellAnimationObject;

    void spawnEffect(double timeToLive);
};

