#pragma once

#include "ItemAbility.h"

class ChoppersHat: public ItemAbility
{
public:
    ChoppersHat(Enums::ResourceTypes rType);
    ChoppersHat() = default;
    virtual ~ChoppersHat() = default;

    // ItemAbility interface
public:
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
    virtual void update(double timestep) override;

private:
    int amount = 0;
    double period = 0;
    double currentTime = 0;
    Enums::ResourceTypes resType = Enums::ResourceTypes::UNKNOWN;
};
