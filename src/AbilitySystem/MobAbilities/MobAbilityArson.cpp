#include "MobAbilityArson.h"

MobAbilityArson::MobAbilityArson()
    :target(nullptr)
{

}

MobAbilityArson::~MobAbilityArson()
{

}

void MobAbilityArson::init(Scene * const scenePtr)
{
    if (casterPtr != nullptr)
    {

    }
}

bool MobAbilityArson::onReady(double timestep)
{
   if (casterPtr != nullptr)
   {
       target = casterPtr->getCurrentTarget();
       if (target != nullptr)
       {
           abilityState = Enums::AbilityStates::asWorking;
       }
   }





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
