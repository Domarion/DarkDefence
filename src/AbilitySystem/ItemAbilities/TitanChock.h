#pragma once
#include "ItemAbility.h"


class TitanChock: public ItemAbility
{
public:
    TitanChock();
    virtual ~TitanChock();

    // ItemAbility interface
public:
    virtual void init(GameScene* const scenePtr) override;
};

