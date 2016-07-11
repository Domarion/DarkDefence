#pragma once
#include "ItemAbility.h"

class SteelShield: public ItemAbility
{
public:
    SteelShield();
    virtual ~SteelShield();
    // ItemAbility interface
public:
    virtual void init(Scene * const scenePtr) override;
};

