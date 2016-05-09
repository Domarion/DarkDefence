/*
 * DestructibleObject.cpp
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "DestructibleObject.h"

DestructibleObject::DestructibleObject()
:Alive( true ), currentHealth(0)
{
	// TODO Auto-generated constructor stub

}

DestructibleObject::~DestructibleObject()

{
	// TODO Auto-generated destructor stub
}

const pair<int, int>& DestructibleObject::getAttackProtection() const
{
	return *attackProtection;
}


const string& DestructibleObject::getName() const
{
	return name;
}
void DestructibleObject::setName(const string& name)
{
	this->name = name;
}

const string& DestructibleObject::getTag() const
{
	return tag;
}

void DestructibleObject::setTag(const string& tag)
{
	this->tag = tag;
}

bool DestructibleObject::IsAlive() const
{
	return Alive;
}

DestructibleObject::DestructibleObject(string aName, string aTag,
		int aMaxHealth, int aProtection[])
:name(aName), tag(aTag), Alive(true), maximumHealth(aMaxHealth, 0), currentHealth(aMaxHealth), worldX ( 0 ), worldY ( 0 )
{
	for(int i = 0; i < DestructibleObject::damageTypesCount; ++i)
	{
		attackProtection[i].first = aProtection[i];
		attackProtection[i].second = 0;
	}
}

int DestructibleObject::getMaximumHealth() const
{
	return maximumHealth.first;
}

void DestructibleObject::setMaximumHealth(int hp)
{
	if (hp < 0)
		return;

	maximumHealth.first = hp;
	if (currentHealth != maximumHealth.first)
		setCurrentHealth(hp);
}

int DestructibleObject::getCurrentHealth() const
{

	return currentHealth;
}

void DestructibleObject::setCurrentHealth(int hp)
{
	if (hp < 0)
		return;

	currentHealth = hp;
}

void DestructibleObject::setIsAlive(bool alive)
{
	Alive = alive;
}

int DestructibleObject::getWorldX() const
{
	return worldX;
}

void DestructibleObject::setWorldX(int worldX)
{
	this->worldX = worldX;
}

int DestructibleObject::getWorldY() const
{
	return worldY;
}

void DestructibleObject::setWorldY(int worldY)
{
	this->worldY = worldY;
}

bool DestructibleObject::receiveDamage(int* damage)
{
    if (damage == nullptr)
        return false;

	int summaryDamage = 0;
	for(int i = 0; i < DestructibleObject::damageTypesCount; ++i)
	{
		int temp = attackProtection[i].first + attackProtection[i].second - damage[i];
		if (temp < 0)
			summaryDamage += temp;
	}
	if (summaryDamage < 0)
	{
		currentHealth += summaryDamage;
		bool result = (currentHealth > 0);
		setIsAlive(result);
		return !result;
	}
    return false;
}

bool DestructibleObject::receiveDamageOneType(int damage_type, int damage)
{
    if (damage_type < 0 || damage_type >= DestructibleObject::damageTypesCount)
        return false;

    int summaryDamage = attackProtection[damage_type].first + attackProtection[damage_type].second - damage;

    if (summaryDamage < 0)
    {
        currentHealth += summaryDamage;
        bool result = (currentHealth > 0);
        setIsAlive(result);
        return !result;
    }
    return false;
}

bool DestructibleObject::addHealth(int amount)
{
    currentHealth += amount;
    if (currentHealth > getMaximumHealth())
    {
        currentHealth = getMaximumHealth();
        return true;
    }

    return false;
}

void DestructibleObject::setProtectionModifier(int modifier)
{
    for(int i = 0; i < DestructibleObject::damageTypesCount; ++i)
    {
        attackProtection[i].second = modifier;
    }
}

int DestructibleObject::getProtectionModifier() const
{
    return attackProtection[0].second;
}
