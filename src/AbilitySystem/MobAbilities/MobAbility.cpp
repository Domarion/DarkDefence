#include "MobAbility.h"

MobAbility::MobAbility()
    :target(nullptr)
{

}

MobAbility::~MobAbility()
{

}

void MobAbility::setTarget(DestructibleObject *targ)
{
    target = targ;
    if (target == nullptr)
        std::cout << "Why target is nullptr?" << std::endl;
}

bool MobAbility::isInProcess()
{
    return !(abilityState == Enums::AbilityStates::asNotAvaliable);
}

bool MobAbility::isTargetable()
{
    return false;
}

