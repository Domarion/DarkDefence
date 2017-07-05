#include "CorruptedPineApple.h"


void CorruptedPineApple::init(std::shared_ptr<Scene> /*scenePtr*/, std::shared_ptr<ManaGlobal> /*aManaModel*/)
{
    string towerName = "CatapultTower";
    auto tower = GameModel::getInstance()->getRootTower()->recursiveSearch(towerName);
    if (tower != nullptr)
    {
        int dmg = tower->getData()->getAttackDamageWithIndex(static_cast<int>(Enums::DamageTypes::dtFIRE)) + 10;
        tower->getData()->setAttackDamageWithIndex(static_cast<int>(Enums::DamageTypes::dtFIRE), dmg);

        int damageArea = tower->getData()->getDamageArea() * 4/3;
        tower->getData()->setDamageArea(damageArea);
        std::string arrowName {"BurningStone"};
        tower->getData()->setArrowName(arrowName);
    }
}
