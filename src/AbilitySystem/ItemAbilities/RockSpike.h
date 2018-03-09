#pragma once

#include "ItemAbility.h"

class RockSpike: public ItemAbility
{

    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
    virtual void update(double timestep) override;

private:
    int amount;
    double period;
    double currentTime;
};

