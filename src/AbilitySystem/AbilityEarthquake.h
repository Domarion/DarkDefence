#pragma once

#include "AbilityModel.h"
#include <list>

class SceneObject;
class EffectModel;

class AbilityEarthquake: public AbilityModel
{
    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

public:

    AbilityEarthquake(std::shared_ptr<ManaGlobal> aManaModel);

    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;
    void setDamagePerSecond(int value);

private:

    int damagePerSecond = 0;
    SceneObjectList affectedMobs;
    std::shared_ptr<EffectModel> stunEffect;
    double counter = 0.0;
};
