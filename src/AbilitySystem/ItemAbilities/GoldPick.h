#pragma once
#include "ItemAbility.h"


class GoldPick: public ItemAbility
{
public:
    GoldPick();
    virtual ~GoldPick();

    // ItemAbility interface
public:
    virtual void init(Scene * const scenePtr) override;
    virtual void update(double timestep) override;
private:
    int amount;
    double period;
    double currentTime;
};

