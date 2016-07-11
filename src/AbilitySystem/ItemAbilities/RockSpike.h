#pragma once
#include "ItemAbility.h"

class RockSpike:public ItemAbility
{
public:
    RockSpike();
    virtual ~RockSpike();

    // ItemAbility interface
public:
    virtual void init(Scene * const scenePtr) override;
    virtual void update(double timestep) override;
private:
    int amount;
    double period;
    double currentTime;
};

