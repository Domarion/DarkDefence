#include "TitanChock.h"

TitanChock::TitanChock()
{

}

TitanChock::~TitanChock()
{

}

void TitanChock::init(Scene* const scenePtr)
{
    string towerName = "CloudTower";
    TreeNode<MobModel>* tower = GameModel::getInstance()->getRootTower()->recursiveSearch(towerName);
    if (tower != nullptr)
    {
        int dmg = tower->getData().getAttackDamageWithIndex(Enums::DamageTypes::dtPSYONICAL) + 5;
        tower->getData().setAttackDamageWithIndex(Enums::DamageTypes::dtPSYONICAL, dmg);
    }
}
