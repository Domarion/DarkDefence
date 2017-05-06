#include "TitanChock.h"

TitanChock::TitanChock()
{

}

TitanChock::~TitanChock()
{

}

void TitanChock::init(std::shared_ptr<Scene> /*scenePtr*/, std::shared_ptr<ManaGlobal> /*aManaModel*/)
{
    string towerName = "CloudTower";
    auto tower = GameModel::getInstance()->getRootTower()->recursiveSearch(towerName);
    if (tower != nullptr)
    {
        tower->getData()->replaceAbilityWithName("MobCloudTowerAbility", "TitanChockUpgrade");
        tower->getData()->addAbilityName( "TitanChockMassSlow");

    }
}
