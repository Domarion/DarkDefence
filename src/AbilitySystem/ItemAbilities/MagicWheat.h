#pragma once

#include "ItemAbility.h"

class MagicWheat: public ItemAbility
{
public:
    MagicWheat(Enums::ResourceTypes rType);
    virtual ~MagicWheat() = default;

    // ItemAbility interface
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
    virtual void update(double timestep) override;

private:
    int amount = 0;
    double period{0.0};
    double currentTime{0.0};
    Enums::ResourceTypes resType = Enums::ResourceTypes::STONE;
};
