/*
 * MobModel.cpp
 *
 *  Created on: 9 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "MobModel.h"

MobModel::MobModel()
:DestructibleObject()
{

	// TODO Auto-generated constructor stub

}

MobModel::~MobModel()
{
	// TODO Auto-generated destructor stub
}


const pair<double, double>& MobModel::getAttackDistance() const
{
	return attackDistance;
}

void MobModel::setAttackDistance(const pair<double, double>& attackDistance)
{
    this->attackDistance = attackDistance;
}

int *MobModel::getAttackDamage()
{
    int* damage = new int[DestructibleObject::damageTypesCount];

    for(int i = 0; i != DestructibleObject::damageTypesCount; ++i)
       damage[i] = attackDamage[i].first + attackDamage[i].second;
    return damage;
}


const pair<double, double>& MobModel::getMoveSpeed() const
{
	return moveSpeed;
}

void MobModel::setMoveSpeed(const pair<double, double>& moveSpeed)
{
	this->moveSpeed = moveSpeed;
}



MobModel::MobModel(string aName, string aTag, int aMaxHealth,
		int aProtection[], int damage[], double distance, double speed, list<string> enemiesTags)
:DestructibleObject(aName, aTag, aMaxHealth, aProtection), attackDistance(distance, 0.0),
 moveSpeed(speed, 0.0), enemyTags(enemiesTags)
{
	for(int i = 0; i < DestructibleObject::damageTypesCount; ++i)
	{
		attackDamage[i].first = damage[i];
		attackDamage[i].second = 0;
	}


}

MobModel::MobModel(const MobModel& right)
{
	name = right.name;
	tag = right.tag;
	maximumHealth = right.maximumHealth;
	currentHealth = right.currentHealth;
	for(int i = 0; i < DestructibleObject::damageTypesCount; ++i)
		attackProtection[i] = right.attackProtection[i];

	for(int i = 0; i < DestructibleObject::damageTypesCount; ++i)
		attackDamage[i] = right.attackDamage[i];
	attackDistance = right.attackDistance;
	moveSpeed = right.moveSpeed;
	enemyTags = right.enemyTags;
}

const list<string>& MobModel::getEnemyTags() const
{
	return enemyTags;
}

bool MobModel::checkDistance(int distanceSqr)
{
	int x = static_cast<int>(attackDistance.first + attackDistance.second);

    std::cout << "distance X = " << (x*x) << std::endl;
	return  (x*x) >= distanceSqr;
}

void MobModel::reload()
{
	reloadTime = reloadTimeMaximum.first + reloadTimeMaximum.second;
}

double MobModel::getReloadTime() const
{
	return reloadTime;
}

void MobModel::setReloadTime(double reloadTime)
{
	this->reloadTime = reloadTime;
}
