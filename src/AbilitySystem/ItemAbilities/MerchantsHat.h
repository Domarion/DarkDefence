#pragma once

#include "ItemAbility.h"

class MerchantsHat: public ItemAbility
{
public:
    MerchantsHat() = default;
    virtual ~MerchantsHat() = default;

    // ItemAbility interface
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
    virtual void update(double timestep) override;

private:
    int pointsAmount = 0;
    double period = 0;
    double currentTime = 0;
};

