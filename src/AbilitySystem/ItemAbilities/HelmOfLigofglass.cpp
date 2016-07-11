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
        int dmg = tower->getData().getAttackDamageWithIndex(Enums::DamageTypes::dtFIRE) + 10;
        tower->getData().setAttackDamageWithIndex(Enums::DamageTypes::dtFIRE, dmg);
    }
}
