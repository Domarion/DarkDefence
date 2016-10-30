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

#include "../AbilitySystem/MobEffectReceiver.h"

#include "../AbilitySystem/MobAbilities/MobAbility.h"

#include "../GlobalScripts/TileMapManager.h"

class AIComponent;
class MobAbility;
class MobEffectReceiver;
class MobModel;


class Mob: public SceneObject, public std::enable_shared_from_this<Mob>
{
public:
    Mob(std::shared_ptr<MobModel> model, std::shared_ptr<TileMapManager> aTileMapPtr = nullptr);
    virtual ~Mob();

    virtual void init(int x, int y) override;

    virtual bool update(double timestep) override;
	virtual void finalize() override;
    virtual string getName() const;
    virtual void setName(const string &value);

    virtual string getTag() const;
    virtual void setTag(const string &value);
    virtual std::shared_ptr<DestructibleObject> getDestructibleObject() const override;
    virtual std::shared_ptr<EffectReceiver> getEffectReceiver() const override;
    virtual std::shared_ptr<MobModel> getModel() const;

    std::shared_ptr<TileMapManager> getTileMapManager() const;
    void setTileMapManager(std::shared_ptr<TileMapManager> aTileMapPtr);
protected:

    std::shared_ptr<MobModel> mobModel;


    std::shared_ptr<MobEffectReceiver>  mobEffectReceiver;
    std::shared_ptr<TileMapManager> tileMapPtr;
    std::unique_ptr<AIComponent> mobAI;

};


