#pragma once
#include "ItemAbility.h"

class GulakiAmulet: public ItemAbility
{
public:
    GulakiAmulet() = default;
    virtual ~GulakiAmulet() = default;
private:

    // ItemAbility interface
public:
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
};
