/*
 * Mob.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "Mob.h"
#include "../GlobalScripts/GameModel.h"



Mob::Mob(MobModel* model, TileMapManager* aTileMapPtr)
:mobModel(model),
  mobEffectReceiver(new MobEffectReceiver()), tileMapPtr(aTileMapPtr), mobAI(nullptr)
{

   mobEffectReceiver->init(mobModel);
   if ( tileMapPtr == nullptr)
   {
       std::cout << "Mob_tileNullptr" << std::endl;
   }

}

void Mob::init(int x, int y)
{
    mobAI = std::make_unique<AIComponent>(shared_from_this());

    SceneObject::init(x, y);

    if (mobModel->getTag() == "Monster")
		GameModel::getInstance()->incMonsterCount();

    //mobAI->initMobAbilities();


}

bool Mob::update(double timestep)
{
	SceneObject::update(timestep);
    if (!mobModel->IsAlive())
    {
        finalize();
        return false;
    }
    mobAI->MakeDecision(timestep);
    return true;
}

void Mob::finalize()
{

    if (mobModel->getTag() == "Monster")
        GameModel::getInstance()->decMonsterCount(mobModel->getName());

}

Mob::~Mob()
{
    delete mobModel;
    delete mobEffectReceiver;
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

DestructibleObject *Mob::getDestructibleObject()
{
    return mobModel;
}

EffectReceiver* Mob::getEffectReceiver() const
{
    return mobEffectReceiver;
}

MobModel *Mob::getModel() const
{
    return mobModel;
}


TileMapManager *Mob::getTileMapManager() const
{
    if (tileMapPtr == nullptr)
    {
        std::cout << "getTileMapManager nullptr " << this->getTag() << std::endl;
    }
    return tileMapPtr;
}

void Mob::setTileMapManager(TileMapManager *aTileMapPtr)
{
    tileMapPtr = aTileMapPtr;
}


