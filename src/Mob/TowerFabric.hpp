#pragma once
#include "Tower.h"
#include "TowerUpgradeController.h"

class TowerUpgradeController;

class Tower;

class TowerFabric
{
public:
    TowerFabric();
    Tower* produceTower(string towerName, TowerUpgradeController* upgrader = nullptr);
};
