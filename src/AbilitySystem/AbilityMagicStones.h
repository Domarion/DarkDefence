#pragma once
#include "AbilityModel.h"
#include "EffectModel.h"

class AbilityMagicStones: public AbilityModel
{
public:
    AbilityMagicStones();
    virtual ~AbilityMagicStones();
    virtual void init(Scene* const scenePtr) override;
    virtual bool onReady(double timestep);
    virtual bool onWorking(double timestep);
    virtual bool onCooldown(double timestep);
private:
    EffectModel StoneEffect;
    SceneObject* gatesSceneObject;
};

