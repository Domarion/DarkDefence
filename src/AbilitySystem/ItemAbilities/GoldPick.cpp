#include "GoldPick.h"

GoldPick::GoldPick()
{

}

GoldPick::~GoldPick()
{

}

void GoldPick::init(GameScene * const scenePtr)
{
    amount = 3;
    currentTime = period = 3000;
    GameModel::getInstance()->setPointsRefundModifier(4);

    map<string, MobModel> mapping = GameModel::getInstance()->getMonsterList();
    for(auto mptr = mapping.begin(); mptr != mapping.end(); ++mptr)
    {
        int newMaxHp =mptr->second.getMaximumHealth() * 2 ;
        mptr->second.setMaximumHealth(newMaxHp);
    }

    AbilityModel* magicStone = scenePtr->getAbilityModelWithName("MagicStones");
    if (magicStone != nullptr)
    {
        int manaCost = static_cast<int>( 0.15 * magicStone->getManaCost());
        magicStone->setManaCost(manaCost);
        double workTime = magicStone->getWorkTime() *1.85;
        magicStone->setWorkTime(workTime);
    }
}

void GoldPick::update(double timestep)
{

    if (currentTime <= 0.0)
    {
        currentTime = period;
        GameModel::getInstance()->getResourcesModel()->addResource(Enums::ResourceTypes::GOLD, amount);
        GameModel::getInstance()->getResourcesModel()->addResource(Enums::ResourceTypes::STONE, amount);
    }
    else
        currentTime -= timestep;
}
