#pragma once
#include "ItemAbility.h"

class CaftanOfGold: public ItemAbility
{
public:
    CaftanOfGold();
    virtual ~CaftanOfGold();

    // ItemAbility interface
public:
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
    virtual void update(double timestep) override;
private:
    int goldAmount;
    double period;
    double currentTime;
};

