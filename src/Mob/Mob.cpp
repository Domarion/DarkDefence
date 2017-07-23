/*
 * Mob.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "Mob.h"
#include "../GlobalScripts/GameModel.h"
#include "Logging/Logger.h"


Mob::Mob(std::shared_ptr<MobModel> model, std::shared_ptr<TileMapManager> aTileMapPtr)
    : mobModel(model)
    , mobEffectReceiver(std::make_shared<MobEffectReceiver>())
    , tileMapPtr(aTileMapPtr)
    , mobAI(nullptr)
{

   mobEffectReceiver->init(mobModel);

   if (!tileMapPtr)
   {
       LOG_ERROR("Tilemap is nullptr.");
   }
}

void Mob::init(int x, int y)
{
    mobAI = std::make_unique<AIComponent>(shared_from_this());

    SceneObject::init(x, y);

    if (mobModel->getTag() == "Monster")
		GameModel::getInstance()->incMonsterCount();
}

bool Mob::update(double timestep)
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
        getEffectReceiver()->processTemporaryEffects(timestep);
    }

    if (mobModel->getIsStunned())
    {
        return true;
    }

    SceneObject::update(timestep);

    if (mobAI != nullptr)
    {
        mobAI->MakeDecision(timestep);
    }

    return true;
}

void Mob::finalize()
{
    mobAI.reset();
    if (mobModel->getTag() == "Monster")
        GameModel::getInstance()->decMonsterCount(mobModel->getName());
}

Mob::~Mob()
{
    tileMapPtr = nullptr;
}

string Mob::getName() const
{
    return mobModel->getName();
}

void Mob::setName(const string &value)
{
    mobModel->setName(value);
}

string Mob::getTag() const
{
    return mobModel->getTag();
}

void Mob::setTag(const string &value)
{
    mobModel->setTag(value);
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


std::shared_ptr<TileMapManager> Mob::getTileMapManager() const
{
    if (!tileMapPtr)
    {
        std::string msg = std::string("TileMapManager is nullptr for ") + this->getName();
        LOG_ERROR(msg);
    }

    return tileMapPtr;
}

void Mob::setTileMapManager(std::shared_ptr<TileMapManager> aTileMapPtr)
{
    tileMapPtr = aTileMapPtr;
}


