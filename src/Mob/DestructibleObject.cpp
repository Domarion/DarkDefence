/*
 * DestructibleObject.cpp
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "DestructibleObject.h"

DestructibleObject::DestructibleObject()
    : Alive(true)
    , currentHealth(0)
    , maximumHealth{0, 0}
{
}

std::array<pair<int, int>, DestructibleObject::damageTypesCount> DestructibleObject::getAttackProtection() const
{
    return attackProtection;
}

const string& DestructibleObject::getName() const
{
	return name;
}

void DestructibleObject::setName(const string& aName)
{
    name = aName;
}

const string& DestructibleObject::getTag() const
{
	return tag;
}

void DestructibleObject::setTag(const string& aTag)
{
    tag = aTag;
}

bool DestructibleObject::IsAlive() const
{
	return Alive;
}

DestructibleObject::DestructibleObject(
    string aName, string aTag, int aMaxHealth, int aProtection[])
    : name(aName)
    , tag(aTag)
    , Alive(true)
    , currentHealth(aMaxHealth)
    , maximumHealth(aMaxHealth, 0)
{
    for(size_t i = 0; i < DestructibleObject::damageTypesCount; ++i)
	{
		attackProtection[i].first = aProtection[i];
		attackProtection[i].second = 0;
    }
}

DestructibleObject::DestructibleObject(const DestructibleObject &right)
{
    if (this != &right)
    {
        name = right.name;
        tag = right.tag;
        maximumHealth = right.maximumHealth;
        currentHealth = right.currentHealth;

        for(size_t i = 0; i < DestructibleObject::damageTypesCount; ++i)
            attackProtection[i] = right.attackProtection[i];
        Alive = right.Alive;
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

    if (currentHealth == maximumHealth.first)
    {
        maximumHealth.first = hp;
		setCurrentHealth(hp);
    }
    else
        maximumHealth.first = hp;
}

int DestructibleObject::getCurrentHealth() const
{

    return currentHealth;
}

void DestructibleObject::connectMethod(std::function<void (int, int)> handler)
{
    connectedMethod = handler;
}

bool DestructibleObject::changeHealth(int amount)
{

    if (currentHealth + amount > getMaximumHealth())
    {
        currentHealth =  getMaximumHealth();

    }
    else
    if (currentHealth + amount  <= 0)
    {
        currentHealth = 0;
        setIsAlive(false);
    }
    else
        currentHealth += amount;

    if (connectedMethod != nullptr)
        connectedMethod(currentHealth,  getMaximumHealth());
    return (currentHealth <= 0);
}

void DestructibleObject::setCurrentHealth(int hp)
{
	if (hp < 0)
		return;

	currentHealth = hp;
}

void DestructibleObject::setIsAlive(bool aAlive)
{
    Alive = aAlive;
}

bool DestructibleObject::receiveDamage(int* damage)
{
    if (damage == nullptr)
        return false;

	int summaryDamage = 0;
    for(size_t i = 0; i < DestructibleObject::damageTypesCount; ++i)
	{
        auto temp = attackProtection[i].first + attackProtection[i].second - damage[i];
		if (temp < 0)
			summaryDamage += temp;
	}
	if (summaryDamage < 0)
        return changeHealth(summaryDamage);

    return false;
}

bool DestructibleObject::receiveDamageOneType(size_t damage_type, int damage)
{
    if (damage_type >= DestructibleObject::damageTypesCount)
        return false;

    auto summaryDamage = attackProtection[damage_type].first + attackProtection[damage_type].second - damage;

    if (summaryDamage < 0)
       return changeHealth(summaryDamage);

    return false;
}

bool DestructibleObject::addHealth(int amount)
{
    bool result = false;

    currentHealth += amount;
    if (currentHealth > getMaximumHealth())
    {
        currentHealth = getMaximumHealth();
        result = true;
    }

    std::cout << "Health added" << std::endl;
    if (connectedMethod != nullptr)
        connectedMethod(currentHealth, getMaximumHealth());

    return result;
}

void DestructibleObject::setProtectionModifier(int modifier)
{
    for(size_t i = 0; i < DestructibleObject::damageTypesCount; ++i)
    {
        attackProtection[i].second = modifier;
    }
}

int DestructibleObject::getProtectionModifier() const
{
    return attackProtection[0].second;
}
