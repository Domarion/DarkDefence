#pragma once
#include "ItemAbility.h"

class HelmOfLigofglass: public ItemAbility
{
public:
    HelmOfLigofglass();
    virtual ~HelmOfLigofglass();

    // ItemAbility interface
public:
    virtual void init(GameScene* const scenePtr) override;
};

