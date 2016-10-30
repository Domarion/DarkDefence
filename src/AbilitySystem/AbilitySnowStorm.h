#pragma once
#include "AbilityModel.h"
#include "EffectModel.h"
#include <memory>
class AbilitySnowStorm: public AbilityModel
{
    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

public:
    AbilitySnowStorm(std::shared_ptr<ManaGlobal> aManaModel);
    virtual ~AbilitySnowStorm() = default;
    virtual void init(std::shared_ptr<Scene> scenePtr);
    virtual bool onReady(double timestep);
    virtual bool onWorking(double timestep);
    virtual bool onCooldown(double timestep);
    void setDamagePerSecond(int value);
private:
    std::shared_ptr<EffectModel> snowEffect;
    int damagePerSecond;
    SceneObjectList affectedMobs;

};

