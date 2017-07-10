#pragma once

#include "ItemAbility.h"

class TitanChock : public ItemAbility
{
public:
    TitanChock() = default;
    virtual ~TitanChock() = default;

    // ItemAbility interface
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
};

