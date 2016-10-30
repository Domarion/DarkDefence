#pragma once
#include "ItemAbility.h"

class UberionsCloak: public ItemAbility
{
public:
    UberionsCloak();
    virtual ~UberionsCloak();


    // ItemAbility interface
public:
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;

};

