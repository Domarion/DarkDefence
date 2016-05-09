#pragma once

#include "../../GlobalScripts/GameModel.h"
#include "../../Scenes/GameScene.h"

class GameModel;

class ItemAbility
{
public:
    ItemAbility();
    virtual ~ItemAbility();
    virtual void init(GameScene* const scenePtr) = 0;
    virtual void update(double timestep);
};
