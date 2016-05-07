#pragma once
#include "ItemAbility.h"

class IceTalisman: public ItemAbility
{
public:
    IceTalisman();
    virtual ~IceTalisman();
    virtual void init(GameScene* const scenePtr) override;
};

