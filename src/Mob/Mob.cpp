/*
 * Mob.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "Mob.h"
#include "../GlobalScripts/GameModel.h"



Mob::Mob(MobModel* model)
:mobModel(model), mobAI(new AIComponent(this)), mobEffectReceiver(new MobEffectReceiver())
{
	// TODO Auto-generated constructor stub

    mobEffectReceiver->init(mobModel);
}

void Mob::init(int x, int y)
{
    SceneObject::init(x, y);

	if (mobAI != nullptr)
    {
        //mobAI->setSprite(spriteModel);
        //mobAI->setScene(parentScenePtr);

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

int Mob::calculateDistanceSqr(Mob *other)
{
    if (other == nullptr)
        return -1;

    int diffX = this->getX() - other->getX();
    int diffY = this->getY() - other->getY();

    return diffX*diffX + diffY*diffY;
}


