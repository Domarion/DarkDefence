#pragma once
#include "ItemAbility.h"

class VampsRod: public ItemAbility
{
public:
    VampsRod();
    virtual ~VampsRod();

    // ItemAbility interface
public:
    virtual void init(Scene * const scenePtr) override;
};
