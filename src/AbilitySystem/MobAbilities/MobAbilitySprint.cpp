#include "MobAbilitySprint.h"
#include "../../Mob/Mob.h"

bool MobAbilitySprint::onReady(double /*timestep*/)
{
     if (target != nullptr)
     {
         std::shared_ptr<Mob> mob = std::dynamic_pointer_cast<Mob>(target);
         if (mob != nullptr)
         {
            double msModifier = mob->getModel()->getMoveSpeedModifier() + 1.5;
            mob->getModel()->setMoveSpeedModifier(msModifier);
            abilityState = Enums::AbilityStates::asWorking;
         }
     }
     else
     {
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
            std::shared_ptr<Mob> mob = std::dynamic_pointer_cast<Mob>(target);
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

bool MobAbilitySprint::canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate)
{
    if (aistate == AIMobStates::aiMOVE || aistate == AIMobStates::aiSELECT)
    {
        target = targ;
        return true;
    }

    return false;
}
