#pragma once

#include "AbilityModel.h"
#include "EffectModel.h"
#include "AbilityAnims/AbilityAnimObject.hpp"

class SceneObject;

class AbilityShrink: public AbilityModel
{
    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

public:

    AbilityShrink(std::shared_ptr<ManaGlobal> aManaModel);

    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;

    void setDamagePerSecond(double value);
    double getDamagePerSecond() const;

private:

    double damagePerSecond{0.0};
    SceneObjectList affectedMobs;
    std::shared_ptr<AbilityAnimObject> spellAnimationObject;
    double counter = 0.0;

    void spawnEffect(double timeToLive);
};

