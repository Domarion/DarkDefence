#pragma once

#include "../../GlobalScripts/GameModel.h"
#include "../../Grouping/Scene.h"

#include "../../GlobalScripts/ManaGlobal.h"
class ItemAbility
{
public:
    ItemAbility();
    virtual ~ItemAbility();
    virtual void init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel) = 0;
    virtual void update(double timestep);
};
