#pragma once
#include "AbilityModel.h"
#include "EffectModel.h"

class AbilitySnowStorm: public AbilityModel
{
public:
    AbilitySnowStorm();
    virtual ~AbilitySnowStorm();
    virtual void init(Scene* const scenePtr);
    virtual bool onReady(double timestep);
    virtual bool onWorking(double timestep);
    virtual bool onCooldown(double timestep);
    void setDamagePerSecond(int value);
private:
    EffectModel snowEffect;
    list<SceneObject*> affectedMobs;
    int damagePerSecond;
};

