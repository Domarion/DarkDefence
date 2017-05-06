#pragma once

#include "ItemAbility.h"

class BurningAxe : public ItemAbility
{
public:
    BurningAxe() = default;
    virtual ~BurningAxe() = default;

    // ItemAbility interface
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
    virtual void update(double timestep) override;

private:
    int amount = 0;
    double period {0.0};
    double currentTime {0.0};
};

