#pragma once
#include "ItemAbility.h"

class UberionsCloak: public ItemAbility
{
public:
    UberionsCloak();
    virtual ~UberionsCloak();


    // ItemAbility interface
public:
    virtual void init(GameScene* const scenePtr) override;

};

