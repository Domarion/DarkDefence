#include "MobAbilityArson.h"

MobAbilityArson::MobAbilityArson()
    : arsonEffect(std::make_shared<EffectModel>())

{
    arsonEffect->setCaption("ArsonEffect");
}

MobAbilityArson::~MobAbilityArson()
{

}



bool MobAbilityArson::onReady(double /*timestep*/)
{
    if (target == nullptr)
    {
        abilityState = Enums::AbilityStates::asNotAvaliable;
        return true;
    }

    target->getEffectReceiver()->applyEffect(arsonEffect);
    abilityState = Enums::AbilityStates::asWorking;
    return true;
}

bool MobAbilityArson::onWorking(double timestep)
{
    if (target == nullptr)
    {
        abilityState = Enums::AbilityStates::asOnCooldown;
        return false;
    }

    if (counter >= 1000)
    {

        int damage = 30;
        target->getDestructibleObject()->receiveDamageOneType(static_cast<int>(Enums::DamageTypes::dtFIRE), damage);

        counter = 0;
    }

    if (currentWorkTime <= 0)
    {
        currentWorkTime = workTime;
        abilityState = Enums::AbilityStates::asOnCooldown;

        target->getEffectReceiver()->cancelEffect(arsonEffect);
        target = nullptr;
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

    return true;
}

bool MobAbilityArson::canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aimobstate)
{
    if (targ == nullptr
            || aimobstate != Enums::AIMobStates::aiATTACK
            || abilityState != Enums::AbilityStates::asNotAvaliable)
        return false;

    if (targ->getTag() != "Mine" || targ->getEffectReceiver() == nullptr || targ->getEffectReceiver()->hasEffect(arsonEffect))
    {
        //std::cout << "what happened?" << std::endl;
        return false;
    }
    target = targ;

    //std::cout << "trololo?" << std::endl;
    return true;
}


