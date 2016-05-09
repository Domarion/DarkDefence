#pragma once
#include "Mob.h"

class Mob;
class TowerFabric
{
public:
    TowerFabric();
    Mob* const produceTower(string towerName);
};
