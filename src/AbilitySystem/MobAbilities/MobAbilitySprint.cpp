#include "MobAbilitySprint.h"
#include "../../Mob/Mob.h"
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
         Mob* mob = dynamic_cast<Mob*>(target);
         if (mob != nullptr)
         {
            double msModifier = mob->getModel()->getMoveSpeedModifier() + 1.5;
            mob->getModel()->setMoveSpeedModifier(msModifier);
            abilityState = Enums::AbilityStates::asWorking;
            std::cout << "Sprint Working" << std::endl;
         }
     }
     else
     {
         std::cout << "Uncastable" << std::endl;
         abilityState = Enums::AbilityStates::asNotAvaliable;
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
            Mob* mob = dynamic_cast<Mob*>(target);
            if (mob != nullptr)
            {
                double msModifier = mob->getModel()->getMoveSpeedModifier() - 0.5;
                mob->getModel()->setMoveSpeedModifier(msModifier);
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

bool MobAbilitySprint::canTrigger(SceneObject *targ, Enums::AIMobStates aistate)
{
    if (aistate == AIMobStates::aiMOVE || aistate == AIMobStates::aiSELECT)
    {
        target = targ;
        return true;
    }
    return false;
}
