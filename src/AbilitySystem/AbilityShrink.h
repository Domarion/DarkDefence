#pragma once
#include "AbilityModel.h"
#include "EffectModel.h"

class AbilityShrink: public AbilityModel
{
public:
    AbilityShrink();
    virtual ~AbilityShrink();
    virtual void init(Scene* const scenePtr);
    virtual bool onReady(double timestep);
    virtual bool onWorking(double timestep);
    virtual bool onCooldown(double timestep);
    void setDamagePerSecond(double value);
private:
    double damagePerSecond;
    list<SceneObject*> affectedMobs;
};

