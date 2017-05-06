#pragma once
#include "ItemAbility.h"

class CaftanOfGold: public ItemAbility
{
public:
    CaftanOfGold();
    virtual ~CaftanOfGold();

    // ItemAbility interface
public:
    virtual void init(std::shared_ptr<Scene>, std::shared_ptr<ManaGlobal> aManaModel) override;
    virtual void update(double timestep) override;
private:
    int pointsAmount = 0;
    double period = 0;
    double currentTime = 0;
};

