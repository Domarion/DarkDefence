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
    int goldAmount;
    double period;
    double currentTime;
};

