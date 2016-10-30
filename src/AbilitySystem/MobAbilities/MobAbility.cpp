#include "MobAbility.h"

MobAbility::MobAbility(std::shared_ptr<ManaGlobal> aManaModel)
    : AbilityModel(aManaModel)
    , target(nullptr)
{

}

MobAbility::~MobAbility()
{

}

void MobAbility::setTarget(std::shared_ptr<SceneObject> targ)
{
    target = targ;
}

bool MobAbility::isInProcess()
{
    return !(abilityState == Enums::AbilityStates::asNotAvaliable);
}

bool MobAbility::isTargetable()
{
    return false;
}
