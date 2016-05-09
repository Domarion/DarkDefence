#include "MobAbility.h"

MobAbility::MobAbility()
    :casterPtr(nullptr)
{

}

MobAbility::~MobAbility()
{

}

void MobAbility::setCaster(Mob *caster)
{
    casterPtr = caster;
}


