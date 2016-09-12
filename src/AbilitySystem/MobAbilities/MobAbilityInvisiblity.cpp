#include "MobAbilityInvisiblity.h"
#include "../../Mob/MobModel.h"
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

        target->getSprite()->setVisible(false);
        abilityState = Enums::AbilityStates::asWorking;
        std::cout << "Invis Working" << std::endl;
    }
    else
    {
        std::cout << "Uncastable" << std::endl;
        abilityState = Enums::AbilityStates::asNotAvaliable;
    }

    return true;
}

bool MobAbilityInvisiblity::onWorking(double timestep)
{

   if (target != nullptr)//И скастован спелл или проведена атака
   {

        //target->getSprite()->setVisible(true);
        //abilityState = Enums::AbilityStates::asOnCooldown;
   }

    return true;
}

bool MobAbilityInvisiblity::onCooldown(double timestep)
{
    return true;
}

bool MobAbilityInvisiblity::canTrigger(SceneObject *targ, Enums::AIMobStates aistate)
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

