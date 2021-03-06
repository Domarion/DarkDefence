#include "Mob.h"
#include "../GlobalScripts/GameModel.h"
#include "Logging/Logger.h"


Mob::Mob(std::shared_ptr<MobModel> model, const TileMapManager& aTileMap)
    : mobModel(model)
    , mobEffectReceiver(std::make_shared<MobEffectReceiver>())
    , tileMap(aTileMap)
{

   mobEffectReceiver->init(mobModel);

   if (!tileMap.isInitialized())
   {
       LOG_ERROR("Tilemap is nullptr.");
   }
}

void Mob::init(int aX, int aY)
{
    mobAI = std::make_unique<AIComponent>(shared_from_this());

    SceneObject::init(aX, aY);

    if (mobModel->getTag() == "Monster")
		GameModel::getInstance()->incMonsterCount();
}

bool Mob::update(double aTimeStep)
{
    if (!mobModel->IsAlive())
    {
        std::string msg = std::string("Destructing ") + this->getName();

        LOG_INFO(msg);

        finalize();
        return false;
    }

    if (getEffectReceiver() != nullptr)
    {
        getEffectReceiver()->processTemporaryEffects(aTimeStep);
    }

    if (mobModel->getIsStunned())
    {
        return true;
    }

    SceneObject::update(aTimeStep);

    if (mobAI != nullptr)
    {
        mobAI->MakeDecision(aTimeStep);
    }

    return true;
}

void Mob::finalize()
{
    mobAI.reset();
    if (mobModel->getTag() == "Monster")
        GameModel::getInstance()->decMonsterCount(mobModel->getName());
}

string Mob::getName() const
{
    return mobModel->getName();
}

void Mob::setName(const string& aName)
{
    mobModel->setName(aName);
}

string Mob::getTag() const
{
    return mobModel->getTag();
}

void Mob::setTag(const string& aTag)
{
    mobModel->setTag(aTag);
}

std::shared_ptr<DestructibleObject> Mob::getDestructibleObject() const
{
    return mobModel;
}

std::shared_ptr<EffectReceiver>  Mob::getEffectReceiver() const
{
    return mobEffectReceiver;
}

std::shared_ptr<MobModel> Mob::getModel() const
{
    return mobModel;
}

TileMapManager& Mob::getTileMapManager()
{
    if (!tileMap.isInitialized())
    {
        std::string msg = std::string("TileMapManager is nullptr for ") + this->getName();
        LOG_ERROR(msg);
    }

    return tileMap;
}

bool Mob::hasValidTileManager() const
{
    return tileMap.isInitialized();
}

void Mob::setTileMapManager(const TileMapManager& aTileMap)
{
    tileMap = aTileMap;
}


