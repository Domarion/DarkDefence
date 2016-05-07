#pragma once
#include "ItemAbility.h"

class IceBoots: public ItemAbility
{
public:
    IceBoots();
    virtual ~IceBoots();


    // ItemAbility interface
public:
    virtual void init(GameScene * const scenePtr) override;
};

