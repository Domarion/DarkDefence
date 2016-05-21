#pragma once
#include "ItemAbility.h"

class FeatherOfChap: public ItemAbility
{
public:
    FeatherOfChap();
    virtual ~FeatherOfChap();
    // ItemAbility interface
public:
    virtual void init(GameScene * const scenePtr) override;

private:
    int amount;
};

