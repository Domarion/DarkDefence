#include "MobAbilityInvulnerablity.h"
#include "../../Mob/Mob.h"

bool MobAbilityInvulnerablity::onReady(double /*timestep*/)
{
     if (target != nullptr)
     {
         std::shared_ptr<Mob> mob = std::dynamic_pointer_cast<Mob>(target);
         if (mob != nullptr)
         {
            mob->getModel()->setProtectionModifier(protectionModifier);
            abilityState = Enums::AbilityStates::asWorking;
         }
     }
     else
     {
         abilityState = Enums::AbilityStates::asNotAvaliable;
     }


    return true;
}

bool MobAbilityInvulnerablity::onWorking(double timestep)
{
    if (currentWorkTime <= 0)
    {
        currentWorkTime = workTime;

        if (target)
        {
            std::shared_ptr<Mob> mob = std::dynamic_pointer_cast<Mob>(target);
            if (mob != nullptr)
            {
                int protModifier = mob->getModel()->getProtectionModifier() - protectionModifier;
                mob->getModel()->setProtectionModifier(protModifier);
            }
        }
        abilityState = Enums::AbilityStates::asOnCooldown;
    }
    else
        currentWorkTime -= timestep;

    return true;
}



bool MobAbilityInvulnerablity::onCooldown(double timestep)
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

bool MobAbilityInvulnerablity::canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate)
{
    if (aistate == AIMobStates::aiMOVE && targ != nullptr && targ->getTag() == "Monster")
    {
        const double allowedPercentage = 0.70;
        double percentage = static_cast<double>(targ->getDestructibleObject()->getCurrentHealth()) / targ->getDestructibleObject()->getMaximumHealth();

        if (percentage < allowedPercentage)
        {
            MobAbility::setTarget(targ);

            return true;
        }
    }

    return false;
}
