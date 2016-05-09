#pragma once
#include "../../Mob/Mob.h"
#include "../AbilityModel.h"

class Mob;

class MobAbility: public AbilityModel
{
public:
    MobAbility();
    virtual ~MobAbility();


    virtual void setCaster(Mob* caster);

protected:

    Mob* casterPtr;
};

