#pragma once
#include "Tower.h"
#include "TowerUpgradeController.h"
#include <vector>
using std::vector;
//#include <memory>

class TowerUpgradeController;

class Tower;

class TowerFabric
{
public:
    TowerFabric();
    ~TowerFabric();
    Tower* produceTower(string towerName, TowerUpgradeController* upgrader = nullptr, TileMapManager *aTileMap = nullptr);
private:
    vector< Tower* > producedTowers;
};
