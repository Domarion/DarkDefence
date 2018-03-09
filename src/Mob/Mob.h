#pragma once

#include "../AI/AIComponent.h"
#include "../Grouping/SceneObject.h"
#include "MobModel.h"

#include "../AbilitySystem/MobEffectReceiver.h"

#include "../GlobalScripts/TileMapManager.h"

class AIComponent;
class MobEffectReceiver;
class MobModel;

class Mob: public SceneObject, public std::enable_shared_from_this<Mob>
{
public:
    Mob(std::shared_ptr<MobModel> model, std::shared_ptr<TileMapManager> aTileMapPtr = nullptr);
    virtual ~Mob() = default;

    virtual void init(int aX, int aY) override;

    virtual bool update(double aTimeStep) override;
	virtual void finalize() override;
    virtual string getName() const override;
    virtual void setName(const string& aName) override;

    string getTag() const override;
    void setTag(const string& aTag) override;
    std::shared_ptr<DestructibleObject> getDestructibleObject() const override;
    std::shared_ptr<EffectReceiver> getEffectReceiver() const override;
     std::shared_ptr<MobModel> getModel() const;

    std::shared_ptr<TileMapManager> getTileMapManager() const;
    void setTileMapManager(std::shared_ptr<TileMapManager> aTileMapPtr);
protected:

    std::shared_ptr<MobModel> mobModel;
    std::shared_ptr<MobEffectReceiver>  mobEffectReceiver;
    std::shared_ptr<TileMapManager> tileMapPtr;
    std::unique_ptr<AIComponent> mobAI;

};


