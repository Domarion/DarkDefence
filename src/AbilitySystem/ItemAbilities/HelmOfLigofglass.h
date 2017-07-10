#pragma once

#include "ItemAbility.h"

class HelmOfLigofglass : public ItemAbility
{
public:
    HelmOfLigofglass() = default;
    virtual ~HelmOfLigofglass() = default;

    // ItemAbility interface
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
};

