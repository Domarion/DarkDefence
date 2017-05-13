#pragma once

#include "AbilityModel.h"
#include "EffectModel.h"
#include <memory>

class AbilitySnowStorm: public AbilityModel
{
    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

public:

    AbilitySnowStorm(std::shared_ptr<ManaGlobal> aManaModel);

    void init(std::shared_ptr<Scene> scenePtr) override;
    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;
    void setDamagePerSecond(int value);

private:

    std::shared_ptr<EffectModel> snowEffect;
    int damagePerSecond;
    SceneObjectList affectedMobs;
    double counter = 0.0;
};

