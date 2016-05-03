/*
 * Mob.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "Mob.h"
#include "../GlobalScripts/GameModel.h"



Mob::Mob(MobModel* model)
:mobModel(model), mobAI(new AIComponent(mobModel))
{
	// TODO Auto-generated constructor stub


}

void Mob::init()
{
	if (mobAI != nullptr)
    {
		mobAI->setSprite(spriteModel);
        mobAI->setScene(parentScenePtr);
    }

    if (mobModel->getTag() == "Monster")
		GameModel::getInstance()->incMonsterCount();

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
    setPos(mobModel->getWorldX(),mobModel->getWorldY());
    return true;
}

void Mob::finalize()
{
    if (mobModel->getTag() == "Monster")
        GameModel::getInstance()->decMonsterCount();
    delete mobAI;
    delete mobModel;
}

Mob::~Mob()
{
    //finalize();
	// TODO Auto-generated destructor stub
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

