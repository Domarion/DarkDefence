#pragma once
#include "ItemAbility.h"

class HelmOfLigofglass: public ItemAbility
{
public:
    HelmOfLigofglass();
    virtual ~HelmOfLigofglass();

    // ItemAbility interface
public:
    virtual void init(std::shared_ptr<Scene> scenePtr) override;
};

