#pragma once
#include "../GraphicsSystem/UI/ScrollList.h"
#include "TowerFabric.hpp"
#include "../Utility/TreeNode.hpp"
#include <vector>
using std::vector;
#include <string>
using std::string;

class TowerFabric;
class Tower;

class TowerUpgradeController
{
public:
    TowerUpgradeController();
    ~TowerUpgradeController();
    void init(Scene* parent);
    void receiveTowerUpgrade(Tower* tower);
    bool menuClickHandler(size_t itemIndex);

private:

    Scene* parentGameScene;

    std::shared_ptr<CFont> arialFont1;
    Tower *cachedTower;
    vector<string> currentTowerChildren;
    ScrollList towerMenu;
    TowerFabric* fabric;
};

