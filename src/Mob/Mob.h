/*
 * Mob.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "../AI/AIComponent.h"
#include "../Grouping/SceneObject.h"
#include "MobModel.h"
#include "MobSpawner.h"

#include "../AbilitySystem/MobEffectReceiver.h"
//#include "../Grouping/SceneObjectFabric.h"

#include "../AbilitySystem/MobAbilities/MobAbility.h"
class MobSpawner;

class AIComponent;
class MobAbility;
class MobEffectReceiver;
class MobModel;

class Mob: public SceneObject
{
    //friend class SceneObjectFabric;
    friend class MobSpawner;
    friend class TowerFabric;
public:
	virtual void init() override;

    virtual bool update(double timestep) override;
	virtual void finalize() override;
    virtual string getName() const;
    virtual void setName(const string &value);

    virtual string getTag() const;
    virtual void setTag(const string &value);
    virtual DestructibleObject* getDestructibleObject() override;
    EffectReceiver* getEffectReceiver() const;
    DestructibleObject* getCurrentTarget();
protected:
    Mob(MobModel* model);
    virtual ~Mob();

    MobModel* mobModel;

	AIComponent* mobAI;
    MobEffectReceiver* mobEffectReceiver;

};


