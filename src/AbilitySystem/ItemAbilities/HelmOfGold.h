#pragma once
#include "ItemAbility.h"

class HelmOfGold: public ItemAbility
{
public:
    HelmOfGold();
    virtual ~HelmOfGold();

    // ItemAbility interface
public:
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
    virtual void update(double timestep) override;

private:
    int pointsAmount = 0;
    double period = 0;
    double currentTime = 0;
};

