/*
 * MobModel.cpp
 *
 *  Created on: 9 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "MobModel.h"
#include "../GlobalScripts/GameModel.h"

MobModel::MobModel()
:DestructibleObject(), attackDistance(0.0, 0.0),
  moveSpeed(0.0, 0.0), reloadTimeMaximum(0.0, 0.0), reloadTime(0.0), damageArea(0), isVisible(true)
{

	// TODO Auto-generated constructor stub
    for(int i = 0; i < DestructibleObject::damageTypesCount; ++i)
        price[i] = 0;

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
        int aProtection[], int damage[], double distance, double speed, double aReloadTime, int aDamageArea, list<EnemyInfo> enemiesTags)
:DestructibleObject(aName, aTag, aMaxHealth, aProtection), attackDistance(distance, 0.0),
 moveSpeed(speed, 0.0), reloadTimeMaximum(aReloadTime, 0.0), reloadTime(aReloadTime), damageArea(aDamageArea), enemiesInfo(enemiesTags), isVisible(true)
{
	for(int i = 0; i < DestructibleObject::damageTypesCount; ++i)
	{
		attackDamage[i].first = damage[i];
		attackDamage[i].second = 0;
	}

    for(int i = 0; i < DestructibleObject::damageTypesCount; ++i)
        price[i] = 0;


}

MobModel::MobModel(const MobModel& right)
    :DestructibleObject(right)
{
    /*name = right.name;
    tag = right.tag;
	maximumHealth = right.maximumHealth;
	currentHealth = right.currentHealth;
	for(int i = 0; i < DestructibleObject::damageTypesCount; ++i)
		attackProtection[i] = right.attackProtection[i];
    */
    if (this != &right)
    {
	for(int i = 0; i < DestructibleObject::damageTypesCount; ++i)
		attackDamage[i] = right.attackDamage[i];
	attackDistance = right.attackDistance;
	moveSpeed = right.moveSpeed;
    enemiesInfo = right.enemiesInfo;
    reloadTimeMaximum = right.reloadTimeMaximum;
    mobAbilitiesNames = right.mobAbilitiesNames;
    for(int i = 0; i < DestructibleObject::damageTypesCount; ++i)
        price[i] = right.price[i];

    isVisible = right.isVisible;

    }

}

const list<EnemyInfo>& MobModel::getEnemyTags() const
{
    return enemiesInfo;
}

bool MobModel::checkDistance(int distanceSqr)
{
    int x = static_cast<int>(attackDistance.first); //+ attackDistance.second);

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

bool MobModel::isMobVisible() const
{
    return isVisible;
}

void MobModel::setMobVisiblity(bool flag)
{
    isVisible = flag;
}



void MobModel::setAbilitiesNames(list<string> abNames)
{
    mobAbilitiesNames = abNames;
}

void MobModel::addAbilityName(std::string name)
{
    mobAbilitiesNames.push_back(name);
}

list<string> &MobModel::getAbilitiesNames()
{
    return mobAbilitiesNames;
}

int *MobModel::getPrice()
{
    return price;
}

int MobModel::getDamageArea() const
{
    return damageArea;
}

void MobModel::setDamageArea(int value)
{
    damageArea = value;
}

