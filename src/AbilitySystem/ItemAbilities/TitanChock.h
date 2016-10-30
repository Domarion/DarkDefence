#pragma once
#include "ItemAbility.h"


class TitanChock: public ItemAbility
{
public:
    TitanChock();
    virtual ~TitanChock();

    // ItemAbility interface
public:
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) override;
};

