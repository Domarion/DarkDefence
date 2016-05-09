#include "MobAbilityArson.h"

MobAbilityArson::MobAbilityArson()

{

}

MobAbilityArson::~MobAbilityArson()
{

}



bool MobAbilityArson::onReady(double timestep)
{
    //std::cout << "WTFArson000" << std::endl;


       if (target != nullptr)
       {
         std::cout << "WTFArson" << std::endl;

           abilityState = Enums::AbilityStates::asWorking;
       }
       else
             abilityState = Enums::AbilityStates::asNotAvaliable;


   return true;
}

bool MobAbilityArson::onWorking(double timestep)
{
    static double counter = 0.0;


    if (target == nullptr)
    {
        abilityState = Enums::AbilityStates::asOnCooldown;
        return false;
    }

    if (counter >= 1000)
    {

        int damage = 30;
        target->receiveDamageOneType(Enums::DamageTypes::dtFIRE, damage);

        std::cout << "AbilityArson Working" << std::endl;
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
        counter += timestep;
    }

    return true;

}

bool MobAbilityArson::onCooldown(double timestep)
{
    if (currentCooldownTime <= 0)
    {
        currentCooldownTime = cooldownTime;
        abilityState = Enums::AbilityStates::asNotAvaliable;
    }
    else
        currentCooldownTime -= timestep;

    return true;
}

bool MobAbilityArson::isTargetable()
{
    std::cout << "TARGETABLE BLYAT" << std::endl;
    return true;
}


