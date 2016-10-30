#pragma once
#include "AbilityModel.h"
#include "EffectModel.h"

class AbilityMagicStones: public AbilityModel
{
public:
    AbilityMagicStones(std::shared_ptr<ManaGlobal> aManaModel);
    virtual ~AbilityMagicStones();
    virtual void init(std::shared_ptr<Scene> scenePtr) override;
    virtual bool onReady(double timestep);
    virtual bool onWorking(double timestep);
    virtual bool onCooldown(double timestep);
private:
    std::shared_ptr<EffectModel> StoneEffect;
    std::shared_ptr<SceneObject> gatesSceneObject;
};

