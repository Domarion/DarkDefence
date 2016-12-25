#include "GulakiAmulet.h"

void GulakiAmulet::init(std::shared_ptr<Scene> /*scenePtr*/, std::shared_ptr<ManaGlobal>)
{
    string towerName = "WindTower";
    auto tower = GameModel::getInstance()->getRootTower()->recursiveSearch(towerName);
    if (tower != nullptr)
    {
        tower->getData()->addAbilityName("GulakiAmulet");
    }
}
