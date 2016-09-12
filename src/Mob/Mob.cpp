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
  mobEffectReceiver(new MobEffectReceiver()), tileMapPtr(aTileMapPtr), mobAI(new AIComponent(this))///TODO:Нельзя инициировать недостроенным объектом!
{
	// TODO Auto-generated constructor stub

    mobEffectReceiver->init(mobModel);
   if ( tileMapPtr == nullptr)
   {
       std::cout << "Mob_tileNullptr" << std::endl;
   }
}

void Mob::init(int x, int y)
{
    SceneObject::init(x, y);

	if (mobAI != nullptr)
    {
        //mobAI->setSprite(spriteModel);
        //mobAI->setScene(parentScenePtr);
       //this->setTileMapManager( getParentScene()->getTileMap());
    }

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
        //parentScenePtr->destroyObject(this);
        return false;
    }
	mobAI->MakeDecision(timestep);
   // setPos(mobModel->getWorldX(),mobModel->getWorldY());
    return true;
}

void Mob::finalize()
{

    if (mobModel->getTag() == "Monster")
        GameModel::getInstance()->decMonsterCount(mobModel->getName());

}

Mob::~Mob()
{

    delete mobAI;
    delete mobModel;
    delete mobEffectReceiver;
    tileMapPtr = nullptr;
    //finalize();

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


