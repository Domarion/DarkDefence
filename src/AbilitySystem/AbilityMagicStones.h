#pragma once

#include "AbilityModel.h"
#include "EffectModel.h"

class SceneObject;
class Scene;

class AbilityMagicStones: public AbilityModel
{
public:
    AbilityMagicStones(std::shared_ptr<ManaGlobal> aManaModel);

    void init(std::shared_ptr<Scene> scenePtr) override;
    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;

private:
    std::shared_ptr<EffectModel> StoneEffect;
    std::shared_ptr<SceneObject> gatesSceneObject;
};

