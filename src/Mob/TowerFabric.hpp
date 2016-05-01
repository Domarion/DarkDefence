#pragma once
#include "Mob.h"
#include "../GlobalScripts/GameModel.h"
class Mob;
class TowerFabric
{
public:
    TowerFabric();
    Mob* const produceTower(string towerName, SDL_Renderer* renderer);
};
