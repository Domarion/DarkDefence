#pragma once
#include "../../Grouping/SceneObject.h"
#include "../AbilityModel.h"
#include "../../Enums.h"
using Enums::AIMobStates;

class MobAbility: public AbilityModel
{
public:
    MobAbility();
    virtual ~MobAbility();


    virtual void setTarget(SceneObject *targ);
    virtual bool isInProcess();
    virtual bool isTargetable();
    virtual bool canTrigger(SceneObject* targ, AIMobStates aistate) = 0;

protected:

    SceneObject* target;
};

