#include "HelmOfLigofglass.h"

HelmOfLigofglass::HelmOfLigofglass()
{

}

HelmOfLigofglass::~HelmOfLigofglass()
{

}

void HelmOfLigofglass::init(std::shared_ptr<Scene> scenePtr, std::shared_ptr<ManaGlobal> aManaModel)
{
    string towerName = "BallistaTower";
    TreeNode<MobModel>* tower = GameModel::getInstance()->getRootTower()->recursiveSearch(towerName);
    if (tower != nullptr)
    {
        int dmg = tower->getData().getAttackDamageWithIndex(static_cast<int>(Enums::DamageTypes::dtFIRE)) + 10;
        tower->getData().setAttackDamageWithIndex(static_cast<int>(Enums::DamageTypes::dtFIRE), dmg);
    }
}
