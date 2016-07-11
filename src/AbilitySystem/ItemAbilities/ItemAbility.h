#pragma once

#include "../../GlobalScripts/GameModel.h"
#include "../../Grouping/Scene.h"

//class GameModel;
class GameScene;
class ItemAbility
{
public:
    ItemAbility();
    virtual ~ItemAbility();
    virtual void init(Scene* const scenePtr) = 0;
    virtual void update(double timestep);
};
