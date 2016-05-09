#pragma once
#include "../../Mob/DestructibleObject.h"
#include "../AbilityModel.h"



class MobAbility: public AbilityModel
{
public:
    MobAbility();
    virtual ~MobAbility();


    virtual void setTarget(DestructibleObject* targ);
    virtual bool isInProcess();
    virtual bool isTargetable();


protected:

    DestructibleObject* target;
};

