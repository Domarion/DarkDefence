#pragma once
#include "AbilityModel.h"

class AbilityEarthquake: public AbilityModel
{
    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;

public:
    AbilityEarthquake();
    virtual ~AbilityEarthquake();
    virtual bool onReady(double timestep) override;
    virtual bool onWorking(double timestep) override;
    virtual bool onCooldown(double timestep) override;
    void setDamagePerSecond(int value);
private:
    int damagePerSecond;
    SceneObjectList affectedMobs;
};
