#pragma once
#include "ItemAbility.h"

class FeatherOfChap: public ItemAbility
{
public:
    FeatherOfChap();
    virtual ~FeatherOfChap();
    // ItemAbility interface
public:
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;

private:
    int amount;
};

