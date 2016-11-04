#pragma once
#include "ItemAbility.h"

class ChoppersHat: public ItemAbility
{
public:
    ChoppersHat(Enums::ResourceTypes rType);
    virtual ~ChoppersHat();

    // ItemAbility interface
public:
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
    virtual void update(double timestep) override;
private:
    int amount;
    double period;
    double currentTime;
    Enums::ResourceTypes resType;
};
