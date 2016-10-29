#pragma once
#include "AbilityModel.h"
#include "EffectModel.h"

class AbilityShrink: public AbilityModel
{
    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

public:
    AbilityShrink();
    virtual ~AbilityShrink();
    virtual void init(std::shared_ptr<Scene> scenePtr);
    virtual bool onReady(double timestep);
    virtual bool onWorking(double timestep);
    virtual bool onCooldown(double timestep);
    void setDamagePerSecond(double value);
    double getDamagePerSecond() const;
private:
    double damagePerSecond;
    SceneObjectList affectedMobs;
};

