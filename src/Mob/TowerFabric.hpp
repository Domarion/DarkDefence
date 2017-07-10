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
    std::shared_ptr<Tower> produceTower(const std::string& aTowerName,
        std::shared_ptr<RenderingSystem>& aRenderingContext,
        std::shared_ptr<TowerUpgradeController> upgrader = nullptr,
        std::shared_ptr<TileMapManager> aTileMap = nullptr);
};
