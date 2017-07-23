#include "MobAbilityInvisiblity.h"
#include "../../Mob/MobModel.h"
#include "Logging/Logger.h"

bool MobAbilityInvisiblity::onReady(double /*timestep*/)
{
    if (target)
    {
        target->getSprite()->setVisible(false);
        abilityState = Enums::AbilityStates::asWorking;
        LOG_INFO("MobAbilityInvisiblity. Has target.");
        return true;

    }

    LOG_INFO("MobAbilityInvisiblity. Has no target.");
    abilityState = Enums::AbilityStates::asNotAvaliable;

    return true;
}

bool MobAbilityInvisiblity::onWorking(double /*timestep*/)
{

   if (target != nullptr)//И скастован спелл или проведена атака
   {
        //target->getSprite()->setVisible(true);
        //abilityState = Enums::AbilityStates::asOnCooldown;
   }

    return true;
}

bool MobAbilityInvisiblity::onCooldown(double /*timestep*/)
{
    return true;
}

bool MobAbilityInvisiblity::canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate)
{
    if (targ == nullptr)
        return false;

    if (abilityState == Enums::AbilityStates::asNotAvaliable)
    {
        target = targ;
        return true;
    }

    if (aistate == Enums::AIMobStates::aiATTACK)
    {
        targ->getSprite()->setVisible(true);
    }

    return false;
}

