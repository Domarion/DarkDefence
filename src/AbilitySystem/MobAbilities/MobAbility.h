#pragma once
#include "../../Grouping/SceneObject.h"
#include "../AbilityModel.h"
#include "../../Enums.h"
using Enums::AIMobStates;

class MobAbility: public AbilityModel
{
public:
    MobAbility(std::shared_ptr<ManaGlobal> aManaModel = nullptr);
    virtual ~MobAbility();


    virtual void setTarget(std::shared_ptr<SceneObject> targ);
    virtual bool isInProcess();
    virtual bool isTargetable();
    virtual bool canTrigger(std::shared_ptr<SceneObject> targ, AIMobStates aistate) = 0;

protected:

    std::shared_ptr<SceneObject> target;
};

