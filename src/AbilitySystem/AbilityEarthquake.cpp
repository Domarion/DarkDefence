#include "AbilityEarthquake.h"
#include "../GlobalScripts/GameModel.h"

AbilityEarthquake::AbilityEarthquake()
 :damagePerSecond(0), affectedMobs( nullptr )
{

}

AbilityEarthquake::~AbilityEarthquake()
{
    if (affectedMobs != nullptr)
    {
        affectedMobs->clear();
        delete affectedMobs;
        affectedMobs = nullptr;
    }
}


bool AbilityEarthquake::onReady(double timestep)
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


        abilityState = Enums::AbilityStates::asWorking;
        std::cout << "worked" << std::endl;
    }
    else
        abilityState = Enums::AbilityStates::asNotAvaliable;

    return true;
}

bool AbilityEarthquake::onWorking(double timestep)
{
    static double counter = 0.0;

    if (counter >= 1000)
    {
        if (affectedMobs!= nullptr && affectedMobs->size() > 0)
            for(auto affectedMob = affectedMobs->begin(); affectedMob != affectedMobs->end(); ++affectedMob)
            {
                if (*affectedMob != nullptr)
                    (*affectedMob)->getDestructibleObject()->receiveDamageOneType(1, damagePerSecond);
            }
        counter = 0;
    }

    if (currentWorkTime <= 0)
    {

        currentWorkTime = workTime;
        abilityState = Enums::AbilityStates::asOnCooldown;
    }
    else
    {
        currentWorkTime -= timestep;
        counter+= timestep;
    }

}

bool AbilityEarthquake::onCooldown(double timestep)
{
    if (currentCooldownTime <= 0)
    {
        affectedMobs->clear();
        delete affectedMobs;
        affectedMobs = nullptr;

        currentCooldownTime = cooldownTime;
        abilityState = Enums::AbilityStates::asNotAvaliable;
    }
    else
        currentCooldownTime -= timestep;

    return true;
}

void AbilityEarthquake::setDamagePerSecond(int value)
{
    damagePerSecond = value;
}