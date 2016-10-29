#include "MobAbilityRegeneration.h"

MobAbilityRegeneration::MobAbilityRegeneration()
{

}

MobAbilityRegeneration::~MobAbilityRegeneration()
{

}

bool MobAbilityRegeneration::onReady(double timestep)
{
    if (target != nullptr)
    {
         //std::cout << "WTFRegeneration" << std::endl;


        abilityState = Enums::AbilityStates::asWorking;
    }


return true;
}

bool MobAbilityRegeneration::onWorking(double timestep)
{
    static double counter = 0.0;


    if (target == nullptr)
    {
        abilityState = Enums::AbilityStates::asOnCooldown;
        return false;
    }

    if (counter >= 1000)
    {
         counter = 0;
        int regen = 30;
        if (target->getDestructibleObject()->addHealth(regen))
        {
            currentWorkTime = workTime;
            abilityState = Enums::AbilityStates::asOnCooldown;
            return false;
        }
        //std::cout << "AbilityRegeneration Working" << std::endl;

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

bool MobAbilityRegeneration::onCooldown(double timestep)
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

bool MobAbilityRegeneration::canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate)
{
    if (targ == nullptr || abilityState != Enums::AbilityStates::asNotAvaliable)
        return false;

    const double allowedPercentage = 0.70;
    double percentage = static_cast<double>(targ->getDestructibleObject()->getCurrentHealth()) / targ->getDestructibleObject()->getMaximumHealth();

    if ( percentage < allowedPercentage)
    {
        target = targ;
        return true;
    }

    return false;
}
