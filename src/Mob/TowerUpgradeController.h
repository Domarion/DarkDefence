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
    void receiveTowerUpgrade(Tower* tower, int x = 0, int y = 0);
    bool menuClickHandler(int itemIndex);

private:

    Scene* parentGameScene;

    TTF_Font* arialFont1;
    Tower *cachedTower;
    vector<string> currentTowerChildren;
    ScrollList towerMenu;
    TowerFabric* fabric;
};

