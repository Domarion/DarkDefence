/*
 * MobModel.cpp
 *
 *  Created on: 9 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "MobModel.h"
#include "../GlobalScripts/GameModel.h"
#include <algorithm>

MobModel::MobModel()
    : DestructibleObject()
    , attackDistance(0.0, 0.0)
    , moveSpeed(0.0, 0.0)
    , reloadTimeMaximum(0.0, 0.0)
    , reloadTime(0.0)
    , damageArea(0)
    , isVisible(true)
    , isStunned(false)
    , arrowName()
{
    for(size_t i = 0; i < DestructibleObject::damageTypesCount; ++i)
        price[i] = 0;
}

const pair<double, double>& MobModel::getAttackDistance() const
{
    return attackDistance;
}

void MobModel::setAttackDistance(const pair<double, double>& aAttackDistance)
{
    attackDistance = aAttackDistance;
}

int* MobModel::getAttackDamage()
{
    int* damage = new int[DestructibleObject::damageTypesCount];

    for(size_t i = 0; i != DestructibleObject::damageTypesCount; ++i)
        damage[i] = attackDamage[i].first + attackDamage[i].second;
    return damage;
}


const pair<double, double>& MobModel::getMoveSpeed() const
{
    return moveSpeed;
}

void MobModel::setMoveSpeed(const pair<double, double>& aMoveSpeed)
{
    moveSpeed = aMoveSpeed;
}

MobModel::MobModel(string aName,
    string aTag,
    int aMaxHealth,
    int aProtection[],
    int damage[],
    double distance,
    double speed,
    double aReloadTime,
    int aDamageArea,
    list<EnemyInfo> enemiesTags,
    std::string aArrowName)
    : DestructibleObject(aName, aTag, aMaxHealth, aProtection), attackDistance(distance, 0.0)
    , moveSpeed(speed, 0.0)
    , reloadTimeMaximum(aReloadTime, 0.0)
    , reloadTime(aReloadTime)
    , damageArea(aDamageArea)
    , enemiesInfo(enemiesTags)
    , isVisible(true)
    , isStunned(false)
    , arrowName(aArrowName)
{
    for(size_t i = 0; i < DestructibleObject::damageTypesCount; ++i)
    {
        attackDamage[i].first = damage[i];
        attackDamage[i].second = 0;
        price[i] = 0;
    }
}

MobModel::MobModel(const MobModel& right)
    : DestructibleObject(right)
{
    if (this != &right)
    {
        for(size_t i = 0; i < DestructibleObject::damageTypesCount; ++i)
            attackDamage[i] = right.attackDamage[i];

        attackDistance = right.attackDistance;
        moveSpeed = right.moveSpeed;
        enemiesInfo = right.enemiesInfo;
        reloadTimeMaximum = right.reloadTimeMaximum;
        mobAbilitiesNames = right.mobAbilitiesNames;

        for(size_t i = 0; i < DestructibleObject::damageTypesCount; ++i)
            price[i] = right.price[i];

        isVisible = right.isVisible;
        isStunned = right.isStunned;
        arrowName = right.arrowName;
    }
}

const std::string& MobModel::getArrowName() const
{
    return arrowName;
}

void MobModel::setArrowName(const std::string& aArrowName)
{
    arrowName = aArrowName;
}

const list<EnemyInfo>& MobModel::getEnemyTags() const
{
    return enemiesInfo;
}

bool MobModel::checkDistance(int distanceSqr)
{
    int x = static_cast<int>(attackDistance.first);
    return  (x*x) >= distanceSqr;
}

void MobModel::setAttackDamageModifier(size_t index, int modifier)
{
    attackDamage[index].second = modifier;
}

int MobModel::getAttackDamageModifier(size_t index)
{
    return attackDamage[index].second;
}

void MobModel::setAttackDamageWithIndex(size_t index, int value)
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

void MobModel::setReloadTime(double aReloadTime)
{
    reloadTime = aReloadTime;
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

void MobModel::replaceAbilityWithName(const std::string& oldName, const std::string& newName)
{
    auto iter = std::find(mobAbilitiesNames.begin(), mobAbilitiesNames.end(), oldName);

    if (iter != mobAbilitiesNames.end())
    {
        *iter = newName;
    }
}

list<string>& MobModel::getAbilitiesNames()
{
    return mobAbilitiesNames;
}

std::array<int, GlobalConstants::resourceTypeCount> MobModel::getPrice()
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

bool MobModel::getIsStunned() const
{
    return isStunned;
}

void MobModel::setIsStunned(bool value)
{
    isStunned = value;
}

