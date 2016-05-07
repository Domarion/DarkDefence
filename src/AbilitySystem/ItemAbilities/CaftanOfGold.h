#pragma once
#include "ItemAbility.h"

class CaftanOfGold: public ItemAbility
{
public:
    CaftanOfGold();
    virtual ~CaftanOfGold();

    // ItemAbility interface
public:
    virtual void init(GameScene* const scenePtr) override;
    virtual void update(double timestep) override;
private:
    int goldAmount;
    double period;
    double currentTime;
};

