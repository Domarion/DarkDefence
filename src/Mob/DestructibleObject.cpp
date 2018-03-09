#include "DestructibleObject.h"

DestructibleObject::DestructibleObject(
    const std::string& aName,
    const std::string& aTag,
    int aMaxHealth,
    std::array<int, GlobalConstants::damageTypeCount>& aProtection)
    : name(aName)
    , tag(aTag)
    , currentHealth(aMaxHealth)
    , maximumHealth(aMaxHealth, 0)
{
    for(size_t i = 0; i < GlobalConstants::damageTypeCount; ++i)
    {
        attackProtection[i].first = aProtection[i];
        attackProtection[i].second = 0;
    }
}

DestructibleObject::DestructibleObject(const DestructibleObject& aRight)
{
    if (this != &aRight)
    {
        connectedMethod = nullptr;

        name = aRight.name;
        tag = aRight.tag;
        maximumHealth = aRight.maximumHealth;
        currentHealth = aRight.currentHealth;

        for(size_t i = 0; i < GlobalConstants::damageTypeCount; ++i)
            attackProtection[i] = aRight.attackProtection[i];
        Alive = aRight.Alive;
    }
}

DestructibleObject& DestructibleObject::operator= (const DestructibleObject& aRight)
{
    if (this != &aRight)
    {
        connectedMethod = nullptr;

        name = aRight.name;
        tag = aRight.tag;
        maximumHealth = aRight.maximumHealth;
        currentHealth = aRight.currentHealth;

        for(size_t i = 0; i < GlobalConstants::damageTypeCount; ++i)
            attackProtection[i] = aRight.attackProtection[i];
        Alive = aRight.Alive;
    }

    return *this;
}

const std::array<pair<int, int>, GlobalConstants::damageTypeCount>& DestructibleObject::getAttackProtection() const
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
    if (!IsAlive())
    {
        return true;
    }

    if (currentHealth + amount > getMaximumHealth())
    {
        currentHealth =  getMaximumHealth();

    }
    else if (currentHealth + amount  <= 0)
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

bool DestructibleObject::receiveDamage(const std::array<int, GlobalConstants::damageTypeCount>& aDamage)
{
    if (!IsAlive())
        return false;

    int summaryDamage = 0;
    for(size_t i = 0; i < GlobalConstants::damageTypeCount; ++i)
    {
        auto temp = attackProtection[i].first + attackProtection[i].second - aDamage[i];
        if (temp < 0)
            summaryDamage += temp;
    }

    if (summaryDamage < 0)
        return changeHealth(summaryDamage);

    return false;
}

bool DestructibleObject::receiveDamageOneType(size_t aDamageType, int aDamage)
{
    if (aDamageType >= GlobalConstants::damageTypeCount)
        return false;

    auto summaryDamage = attackProtection[aDamageType].first + attackProtection[aDamageType].second - aDamage;

    if (summaryDamage < 0)
        return changeHealth(summaryDamage);

    return false;
}

bool DestructibleObject::addHealth(int aAmount)
{
    bool isMaximumReached = false;

    if (!IsAlive())
    {
        return isMaximumReached;
    }

    currentHealth += aAmount;
    if (currentHealth > getMaximumHealth())
    {
        currentHealth = getMaximumHealth();
        isMaximumReached = true;
    }

    if (connectedMethod != nullptr)
        connectedMethod(currentHealth, getMaximumHealth());

    return isMaximumReached;
}

void DestructibleObject::setProtectionModifier(int aModifier)//TODO почему для всех?
{
    for(size_t i = 0; i < GlobalConstants::damageTypeCount; ++i)
    {
        attackProtection[i].second = aModifier;
    }
}

int DestructibleObject::getProtectionModifier() const
{
    return attackProtection[0].second;
}
