#pragma once

#include "ItemAbility.h"

class MonolithShard: public ItemAbility
{
public:
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
    virtual void update(double timestep) override;

private:
    double currentTime = 0.0;
    double period = 5000.0;

    std::shared_ptr<DestructibleObject> gatesDestructible = nullptr;
};

