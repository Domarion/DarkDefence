#include "RockSpike.h"
#include "../AbilityPrick.h"
RockSpike::RockSpike()
{

}

RockSpike::~RockSpike()
{

}

void RockSpike::init(GameScene * const scenePtr)
{
    amount = 3;
    currentTime = period = 3000;

    AbilityPrick* prick = dynamic_cast<AbilityPrick*>(scenePtr->getAbilityModelWithName("Prick"));
    if (prick != nullptr)
    {
        int dmg = static_cast<int>( 1.5 * prick->getDamage());
        prick->setDamage(dmg);
        double cooldown = static_cast<int>( prick->getCooldownTime() *0.5);
        prick->setCooldownTime(cooldown);
    }
}


void RockSpike::update(double timestep)
{

    if (currentTime <= 0.0)
    {
        currentTime = period;
        GameModel::getInstance()->getResourcesModel()->addResource(Enums::ResourceTypes::STONE, amount);
    }
    else
        currentTime -= timestep;

}
