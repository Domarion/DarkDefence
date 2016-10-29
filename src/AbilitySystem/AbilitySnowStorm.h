#pragma once
#include "AbilityModel.h"
#include "EffectModel.h"
#include <memory>
class AbilitySnowStorm: public AbilityModel
{
    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

public:
    AbilitySnowStorm();
    virtual ~AbilitySnowStorm();
    virtual void init(std::shared_ptr<Scene> scenePtr);
    virtual bool onReady(double timestep);
    virtual bool onWorking(double timestep);
    virtual bool onCooldown(double timestep);
    void setDamagePerSecond(int value);
private:
    EffectModel snowEffect;
    int damagePerSecond;
    SceneObjectList affectedMobs;

};

