#include "GulakiAmulet.h"

void GulakiAmulet::init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal>)
{
    string towerName = "WindTower";
    TreeNode<MobModel>* tower = GameModel::getInstance()->getRootTower()->recursiveSearch(towerName);
    if (tower != nullptr)
    {

        auto Data = tower->getData();
        Data.addAbilityName("GulakiAmulet");
        tower->setData(Data);
    }
}
