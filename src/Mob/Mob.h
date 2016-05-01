/*
 * Mob.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "../AI/AIComponent.h"
#include "../GraphicsSystem/Sprite.h"
#include "../Grouping/SceneObject.h"
#include "MobModel.h"
#include "MobSpawner.h"
#include "TowerFabric.hpp"
//#include "../Grouping/SceneObjectFabric.h"

class MobSpawner;
class TowerFabric;
class AIComponent;

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
private:
    Mob(MobModel* model);
	~Mob();

    MobModel* mobModel;
	AIComponent* mobAI;
	//Sprite mobSprite;
};


