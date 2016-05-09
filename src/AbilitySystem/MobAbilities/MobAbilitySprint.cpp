#include "MobAbilitySprint.h"
#include "../../Mob/MobModel.h"
#include <iostream>

MobAbilitySprint::MobAbilitySprint()
{

}

MobAbilitySprint::~MobAbilitySprint()
{

}

bool MobAbilitySprint::onReady(double timestep)
{
     std::cout << "WTF" << std::endl;
    if (target != nullptr)
    {
        MobModel* mob =  dynamic_cast<MobModel*>(target);
        if (mob != nullptr)
        {
            double msModifier = mob->getMoveSpeedModifier() + 1.5;
            mob->setMoveSpeedModifier(msModifier);
            abilityState = Enums::AbilityStates::asWorking;
            std::cout << "Sprint Working" << std::endl;
        }
        else
        {
            std::cout << "Uncastable" << std::endl;
            abilityState = Enums::AbilityStates::asNotAvaliable;
        }
    }

    return true;
}

bool MobAbilitySprint::onWorking(double timestep)
{

    if (currentWorkTime <= 0)
    {
        currentWorkTime = workTime;

        if (target != nullptr)
        {
            MobModel* mob =  dynamic_cast<MobModel*>(target);
            if (mob != nullptr)
            {
                double msModifier = mob->getMoveSpeedModifier() - 0.5;
                mob->setMoveSpeedModifier(msModifier);
            }
        }
        abilityState = Enums::AbilityStates::asOnCooldown;
    }
    else
        currentWorkTime -= timestep;

    return true;
}



bool MobAbilitySprint::onCooldown(double timestep)
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
