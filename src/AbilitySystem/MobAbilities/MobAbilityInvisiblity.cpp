#include "MobAbilityInvisiblity.h"

MobAbilityInvisiblity::MobAbilityInvisiblity()
{

}

MobAbilityInvisiblity::~MobAbilityInvisiblity()
{

}

bool MobAbilityInvisiblity::onReady(double timestep)
{
    if (target != nullptr)
    {
        MobModel* mob =  dynamic_cast<MobModel*>(target);
        if (mob != nullptr)
        {

            mob->setMobVisiblity(false);
            abilityState = Enums::AbilityStates::asWorking;
            std::cout << "Invis Working" << std::endl;
        }
        else
        {
            std::cout << "Uncastable" << std::endl;
            abilityState = Enums::AbilityStates::asNotAvaliable;
        }
    }
    return true;
}

bool MobAbilityInvisiblity::onWorking(double timestep)
{
    if (currentWorkTime <= 0)
    {
        currentWorkTime = workTime;

        if (target != nullptr)
        {
            MobModel* mob =  dynamic_cast<MobModel*>(target);
            if (mob != nullptr)
            {
                 mob->setMobVisiblity(true);
            }
        }
        abilityState = Enums::AbilityStates::asOnCooldown;
    }
    else
        currentWorkTime -= timestep;

    return true;
}

bool MobAbilityInvisiblity::onCooldown(double timestep)
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
