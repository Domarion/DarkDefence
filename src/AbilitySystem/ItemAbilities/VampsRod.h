#pragma once
#include "ItemAbility.h"

class VampsRod: public ItemAbility
{
public:
    VampsRod();
    virtual ~VampsRod();

    // ItemAbility interface
public:
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
};
