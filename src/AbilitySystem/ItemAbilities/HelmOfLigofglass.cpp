#include "HelmOfLigofglass.h"

HelmOfLigofglass::HelmOfLigofglass()
{

}

HelmOfLigofglass::~HelmOfLigofglass()
{

}

void HelmOfLigofglass::init(Scene* const scenePtr)
{
    string towerName = "BallistaTower";
    TreeNode<MobModel>* tower = GameModel::getInstance()->getRootTower()->recursiveSearch(towerName);
    if (tower != nullptr)
    {
        int dmg = tower->getData().getAttackDamageWithIndex(static_cast<int>(Enums::DamageTypes::dtFIRE)) + 10;
        tower->getData().setAttackDamageWithIndex(static_cast<int>(Enums::DamageTypes::dtFIRE), dmg);
    }
}
