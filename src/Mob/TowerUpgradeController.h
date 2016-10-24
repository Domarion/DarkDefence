#pragma once
#include "../GraphicsSystem/newSystem/ConcreteUIViews/UIScrollList.h"
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
    void init(Scene* parent, std::shared_ptr<RenderingSystem> &aRenderer);
    void receiveTowerUpgrade(Tower* tower);
    bool menuClickHandler(size_t itemIndex);
    bool closeHandler(size_t itemIndex);

private:

    Scene* parentGameScene;

    Tower *cachedTower;
    vector<string> currentTowerChildrenNames;
    std::shared_ptr<UIScrollList> towerMenu;
    TowerFabric* fabric;
    std::shared_ptr<RenderingSystem> renderer;
    std::shared_ptr<ConcreteComposite> upgradeGroup;
};

