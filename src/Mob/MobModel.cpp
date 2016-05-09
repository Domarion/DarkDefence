/*
 * MobModel.cpp
 *
 *  Created on: 9 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "MobModel.h"
#include "../GlobalScripts/GameModel.h"

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
    reloadTimeMaximum = right.reloadTimeMaximum;
    mobAbilitiesNames = right.mobAbilitiesNames;
}

const list<string>& MobModel::getEnemyTags() const
{
	return enemyTags;
}

bool MobModel::checkDistance(int distanceSqr)
{
	int x = static_cast<int>(attackDistance.first + attackDistance.second);

   // std::cout << "distance X = " << (x*x) << std::endl;
    return  (x*x) >= distanceSqr;
}

void MobModel::setAttackDamageModifier(int index, int modifier)
{
    attackDamage[index].second = modifier;
}

int MobModel::getAttackDamageModifier(int index)
{
    return attackDamage[index].second;
}

void MobModel::setAttackDamageWithIndex(int index, int value)
{
    attackDamage[index].first = value;
}

int MobModel::getAttackDamageWithIndex(int index)
{
    return attackDamage[index].first;
}

void MobModel::setMoveSpeedModifier(double modifier)
{
    moveSpeed.second = modifier;
}

double MobModel::getMoveSpeedModifier() const
{
    return moveSpeed.second;
}

void MobModel::setAttackDistanceModifier(double modifier)
{
    attackDistance.second = modifier;
}

double MobModel::getAttackDistanceModifier() const
{
    return attackDistance.second;
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

void MobModel::setReloadTimeMaximum(double reloadTimeMax)
{
    reloadTimeMaximum.first = reloadTimeMax;
}

double MobModel::getReloadTimeModifier() const
{
    return reloadTimeMaximum.second;
}

void MobModel::setReloadTimeModifier(double modifier)
{
    reloadTimeMaximum.second = modifier;
}

void MobModel::initMobAbilities(Mob* caster)
{

    std::cout << "MobName = " << getName() << " INITMOBABS size = " << mobAbilitiesNames.size() << std::endl;

    for(auto ptr = mobAbilitiesNames.begin(); ptr != mobAbilitiesNames.end(); ++ptr)
    {

        mobAbilities.push_back(GameModel::getInstance()->getMobAbilityByName(*ptr));
        mobAbilities.back()->setCaster(caster);
        std::cout << (*ptr) << std::endl;
    }
}

void MobModel::setAbilitiesNames(list<string> abNames)
{
    mobAbilitiesNames = abNames;
}

