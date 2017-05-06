#include "AbilityMagicBlink.h"
#include "../GlobalScripts/GameModel.h"

AbilityMagicBlink::AbilityMagicBlink(std::shared_ptr<ManaGlobal> aManaModel)
    : AbilityModel(aManaModel)
    , damage(0)
{

}

void AbilityMagicBlink::init(std::shared_ptr<Scene> scenePtr)
{
    AbilityModel::init(scenePtr);
}

bool AbilityMagicBlink::onReady(double timestep)
{
    if (AbilityModel::onReady(timestep) == false)
    {
        abilityState = Enums::AbilityStates::asNotAvaliable;

        return false;
    }


    if (affectedMobs == nullptr && parentScenePtr != nullptr && GameModel::getInstance()->getMonsterCount() > 0)
        affectedMobs = parentScenePtr->findObjectsByTag("Monster");

    if (affectedMobs != nullptr)
    {
        if (affectedMobs != nullptr && affectedMobs->size() > 0)
            for(auto affectedMob = affectedMobs->begin(); affectedMob != affectedMobs->end(); ++affectedMob)
            {
                if (*affectedMob != nullptr && (*affectedMob)->getDestructibleObject() != nullptr)
                {
                    (*affectedMob)->setVisible(true);
                    (*affectedMob)->getDestructibleObject()->receiveDamageOneType(3, damage);
                }
            }
        abilityState = Enums::AbilityStates::asOnCooldown;
        affectedMobs->clear();
    }
    else
        abilityState = Enums::AbilityStates::asNotAvaliable;

    return true;
}

bool AbilityMagicBlink::onWorking(double /*timestep*/)
{
    return true;
}

int AbilityMagicBlink::getDamage() const
{
    return damage;
}

void AbilityMagicBlink::setDamage(int value)
{
    damage = value;
}

bool AbilityMagicBlink::update(double timestep)
{
    switch(abilityState)
    {
        case Enums::AbilityStates::asReady:
        {
            onReady(timestep);
            break;
        }

        case Enums::AbilityStates::asWorking:
        {
            onWorking(timestep);
            break;
        }
        case Enums::AbilityStates::asOnCooldown:
        {
            onCooldown(timestep);
            break;
        }
        case Enums::AbilityStates::asNotAvaliable:
        {
            break;
        }
    }

    return true;
}
