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
    virtual void init(std::shared_ptr<Scene> scenePtr) = 0;
    virtual void update(double timestep);
};
