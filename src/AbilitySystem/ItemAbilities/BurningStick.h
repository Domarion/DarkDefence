#pragma once
#include "ItemAbility.h"

class BurningStick: public ItemAbility
{
public:
    BurningStick();
    virtual ~BurningStick();

private:
    int amount;
    double period;
    double currentTime;

    // ItemAbility interface
public:
    virtual void init(std::shared_ptr<Scene> scenePtr) override;
    virtual void update(double timestep) override;
};

