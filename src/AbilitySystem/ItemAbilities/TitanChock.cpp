#include "TitanChock.h"

TitanChock::TitanChock()
{

}

TitanChock::~TitanChock()
{

}

void TitanChock::init(std::shared_ptr<Scene> scenePtr)
{
    string towerName = "CloudTower";
    TreeNode<MobModel>* tower = GameModel::getInstance()->getRootTower()->recursiveSearch(towerName);
    if (tower != nullptr)
    {
        int dmg = tower->getData().getAttackDamageWithIndex(static_cast<int>(Enums::DamageTypes::dtCOLD)) + 5;
        tower->getData().setAttackDamageWithIndex(static_cast<int>(Enums::DamageTypes::dtCOLD), dmg);
    }
}
