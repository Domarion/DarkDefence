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

class TowerUpgradeController: public std::enable_shared_from_this<TowerUpgradeController>
{
public:
    TowerUpgradeController();
    ~TowerUpgradeController();
    void init(std::shared_ptr<Scene> parent, std::shared_ptr<RenderingSystem> &aRenderer);
    void receiveTowerUpgrade(std::shared_ptr<Tower> tower);
    bool menuClickHandler(size_t itemIndex);
    bool closeHandler(size_t itemIndex);

private:

    void stub(std::string){}
    std::shared_ptr<Scene> parentGameScene;

    std::shared_ptr<Tower> cachedTower;
    vector<string> currentTowerChildrenNames;
    std::shared_ptr<UIScrollList> towerMenu;
    std::unique_ptr<TowerFabric> fabric;
    std::shared_ptr<RenderingSystem> renderer;
    std::shared_ptr<ConcreteComposite> upgradeGroup;
};

