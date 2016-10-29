#pragma once
#include "AbilityModel.h"
#include "EffectModel.h"

class AbilityMagicStones: public AbilityModel
{
public:
    AbilityMagicStones();
    virtual ~AbilityMagicStones();
    virtual void init(std::shared_ptr<Scene> scenePtr) override;
    virtual bool onReady(double timestep);
    virtual bool onWorking(double timestep);
    virtual bool onCooldown(double timestep);
private:
    EffectModel StoneEffect;
    std::shared_ptr<SceneObject> gatesSceneObject;
};

