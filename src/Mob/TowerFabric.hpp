#pragma once

#include <vector>

#include "Tower.h"
#include "TowerUpgradeController.h"

using std::vector;

class TowerUpgradeController;

// TODO: why class, may be free function?
class TowerFabric
{
public:
    std::shared_ptr<Tower> produceTower(const std::string& aTowerName,
        std::shared_ptr<RenderingSystem>& aRenderingContext,
        std::shared_ptr<TowerUpgradeController> upgrader = nullptr,
        std::shared_ptr<TileMapManager> aTileMap = nullptr);
};
