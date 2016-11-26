#pragma once
#include "ItemAbility.h"

class GulakiAmulet: public ItemAbility
{
public:

private:

    // ItemAbility interface
public:
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
};
