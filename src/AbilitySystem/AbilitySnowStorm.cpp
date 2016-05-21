#include "AbilitySnowStorm.h"
#include "../GlobalScripts/GameModel.h"
AbilitySnowStorm::AbilitySnowStorm()
{

}

AbilitySnowStorm::~AbilitySnowStorm()
{

}

void AbilitySnowStorm::init(Scene * const scenePtr)
{
    AbilityModel::init(scenePtr);


    pair<string, double> mv = std::make_pair("MoveSpeed", -2.0);
    pair<string, double> rt = std::make_pair("ReloadTime", +5.0e+3);
    snowEffect.addMiniEffect(mv);
    snowEffect.addMiniEffect(rt);

}

bool AbilitySnowStorm::onReady(double timestep)
{


    if (AbilityModel::onReady(timestep) == false)
    {
        abilityState = Enums::AbilityStates::asNotAvaliable;

        return false;
    }

    if (affectedMobs.size() == 0 && parentScenePtr != nullptr && GameModel::getInstance()->getMonsterCount() > 0)
        affectedMobs = (parentScenePtr->findObjectsByTag("Monster"));

    if (affectedMobs.size() > 0)
    {
        for(auto affectedMob = affectedMobs.begin(); affectedMob != affectedMobs.end(); ++affectedMob)
        {
            if (*affectedMob != nullptr)
                (*affectedMob)->getEffectReceiver()->applyEffect(&snowEffect);
        }

        abilityState = Enums::AbilityStates::asWorking;
        std::cout << "worked" << std::endl;
    }
    else
        abilityState = Enums::AbilityStates::asNotAvaliable;

    return true;
}

bool AbilitySnowStorm::onWorking(double timestep)
{
    static double counter = 0.0;

    if (counter >= 1000)
    {
        if (affectedMobs.size() > 0)
            for(auto affectedMob = affectedMobs.begin(); affectedMob != affectedMobs.end(); ++affectedMob)
            {
                if (*affectedMob != nullptr)
                    (*affectedMob)->getDestructibleObject()->receiveDamageOneType(2, damagePerSecond);
            }
        counter = 0;
    }

    if (currentWorkTime <= 0)
    {
        if (affectedMobs.size() > 0)
            for(auto affectedMob = affectedMobs.begin(); affectedMob != affectedMobs.end(); ++affectedMob)
            {
                if (*affectedMob != nullptr)
                    (*affectedMob)->getEffectReceiver()->cancelEffect(&snowEffect);
            }


        currentWorkTime = workTime;
        abilityState = Enums::AbilityStates::asOnCooldown;
    }
    else
    {
        currentWorkTime -= timestep;
        counter+= timestep;
    }

    //std::cout << "worked" << std::endl;
    return true;
}

bool AbilitySnowStorm::onCooldown(double timestep)
{
    if (currentCooldownTime <= 0)
    {
        affectedMobs.clear();
        currentCooldownTime = cooldownTime;
        abilityState = Enums::AbilityStates::asNotAvaliable;
    }
    else
        currentCooldownTime -= timestep;

    return true;
}

void AbilitySnowStorm::setDamagePerSecond(int value)
{
    damagePerSecond = value;
}
