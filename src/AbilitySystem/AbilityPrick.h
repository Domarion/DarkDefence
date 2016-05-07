#pragma once
#include "AbilityModel.h"

class AbilityPrick: public AbilityModel
{
public:
    AbilityPrick();

    // AbilityModel interface
public:
    virtual void init(Scene * const scenePtr) override;
    virtual bool onReady(double timestep) override;
    virtual bool onWorking(double timestep) override;
    virtual bool onCooldown(double timestep) override;
    int getDamage() const;
    void setDamage(int value);

private:
    int damage;
};

