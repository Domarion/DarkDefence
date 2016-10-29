#pragma once
#include "Tower.h"
#include "TowerUpgradeController.h"
#include <vector>
using std::vector;

class TowerUpgradeController;

class TowerFabric
{
public:
    TowerFabric() = default;
    ~TowerFabric() = default;
    std::shared_ptr<Tower> produceTower(string towerName, std::shared_ptr<RenderingSystem> &aRenderingContext, std::shared_ptr<TowerUpgradeController> upgrader = nullptr, TileMapManager *aTileMap = nullptr);
};
