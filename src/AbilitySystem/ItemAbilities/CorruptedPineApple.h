#pragma once
#include "ItemAbility.h"

class CorruptedPineApple: public ItemAbility
{
public:
    CorruptedPineApple() = default;
    virtual ~CorruptedPineApple() = default;

    // ItemAbility interface
public:
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
};

