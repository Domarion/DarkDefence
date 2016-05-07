#pragma once
#include "ItemAbility.h"

class HelmOfGold: public ItemAbility
{
public:
    HelmOfGold();
    virtual ~HelmOfGold();

    // ItemAbility interface
public:
    virtual void init(GameScene* const scenePtr) override;
    virtual void update(double timestep) override;

private:
    int goldAmount;
    double period;
    double currentTime;
};

