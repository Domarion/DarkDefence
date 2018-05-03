#pragma once

#include <string>
#include <vector>

#include "../GraphicsSystem/newSystem/ConcreteUIViews/UIScrollList.h"
#include "../Utility/TreeNode.hpp"

using std::string;
using std::vector;

class Tower;
class Scene;
class TileMapManager;

class TowerUpgradeController
{
public:

    void init(std::shared_ptr<Scene> parent, std::shared_ptr<RenderingSystem> &aRenderer);
    void receiveTowerUpgrade(std::shared_ptr<Tower> tower);
    bool menuClickHandler(size_t itemIndex);
    void closeHandler(std::string);
    std::shared_ptr<Tower> ProduceTower(const std::string& aTowerName, const TileMapManager& aTileMap, size_t aDrawPriority);

private:

    void stub(std::string){}
    std::shared_ptr<Scene> parentGameScene;

    std::shared_ptr<Tower> cachedTower;
    vector<string> currentTowerChildrenNames;
    std::shared_ptr<UIScrollList> towerMenu;
    std::shared_ptr<RenderingSystem> renderer;
    std::shared_ptr<ConcreteComposite> upgradeGroup;
};

