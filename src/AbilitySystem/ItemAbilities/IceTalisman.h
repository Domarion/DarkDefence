#pragma once
#include "ItemAbility.h"

class IceTalisman: public ItemAbility
{
public:
    IceTalisman();
    virtual ~IceTalisman();
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
};

