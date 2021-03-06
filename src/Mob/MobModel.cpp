/*
 * MobModel.cpp
 *
 *  Created on: 9 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "MobModel.h"
#include "../GlobalScripts/GameModel.h"
#include <algorithm>

MobModel::MobModel(const std::string& aName,
    const std::string& aTag,
    int aMaxHealth,
    std::array<int, GlobalConstants::damageTypeCount>& aProtection,
    std::array<int, GlobalConstants::damageTypeCount>& aDamage,
    double aDistance,
    double aSpeed,
    double aReloadTime,
    int aDamageArea,
    list<EnemyInfo> aEnemiesTags,
    const std::string& aArrowName)
    : DestructibleObject(aName, aTag, aMaxHealth, aProtection)
    , attackDistance(aDistance, 0.0)
    , moveSpeed(aSpeed, 0.0)
    , reloadTimeMaximum(aReloadTime, 0.0)
    , reloadTime(0)
    , damageArea(aDamageArea)
    , enemiesInfo(aEnemiesTags)
    , arrowName(aArrowName)
{
    for(size_t i = 0; i < GlobalConstants::damageTypeCount; ++i)
    {
        attackDamage[i].first = aDamage[i];
        attackDamage[i].second = 0;
    }
}

const pair<double, double>& MobModel::getAttackDistance() const
{
    return attackDistance;
}

void MobModel::setAttackDistance(const pair<double, double>& aAttackDistance)
{
    attackDistance = aAttackDistance;
}

std::array<int, GlobalConstants::damageTypeCount> MobModel::getAttackDamage()
{
    std::array<int, GlobalConstants::damageTypeCount> damage;

    for(size_t i = 0; i < GlobalConstants::damageTypeCount; ++i)
    {
        damage[i] = attackDamage[i].first + attackDamage[i].second;
    }

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


MobModel::MobModel(const MobModel& right)
    : DestructibleObject(right)
{
    if (this != &right)
    {
        std::copy(right.attackDamage.begin(), right.attackDamage.end(), attackDamage.begin());

        attackDistance = right.attackDistance;
        moveSpeed = right.moveSpeed;
        enemiesInfo = right.enemiesInfo;
        reloadTimeMaximum = right.reloadTimeMaximum;
        reloadTime = right.reloadTime;
        mobAbilitiesNames = right.mobAbilitiesNames;

        std::copy(right.price.begin(), right.price.end(), price.begin());

        arrowName = right.arrowName;
        isVisible = right.isVisible;
        isStunned = right.isStunned;
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

int MobModel::getAttackDamageWithIndex(size_t index)
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
    reloadTime = 0;
}

double MobModel::getReloadTimeCurrent() const
{
    return reloadTime;
}

void MobModel::setReloadTimeCurrent(double aReloadTime)
{
    reloadTime = aReloadTime;
}

void MobModel::setReloadTimeMaximumBase(double reloadTimeMax)
{
    reloadTimeMaximum.first = reloadTimeMax;
}

double MobModel::getReloadTimeMaximumModifier() const
{
    return reloadTimeMaximum.second;
}

void MobModel::setReloadTimeMaximumModifier(double modifier)
{
    reloadTimeMaximum.second = modifier;
}

double MobModel::getReloadTimeMaximumBase() const
{
    return reloadTimeMaximum.first;
}

bool MobModel::IsReloadingInProgress() const
{
    const double EPSe3 = 1e-3;
    double reloadTimeDiff = reloadTime - reloadTimeMaximum.first - reloadTimeMaximum.second;
    return reloadTimeDiff < EPSe3;
}

void MobModel::ProcessReloadStep(double aTimeStep)
{
    reloadTime += aTimeStep;
}

bool MobModel::isMobVisible() const
{
    return isVisible;
}

void MobModel::setMobVisiblity(bool aIsVisible)
{
    isVisible = aIsVisible;
}

void MobModel::setAbilitiesNames(const list<string>& aAbilityNamesList)
{
    mobAbilitiesNames = aAbilityNamesList;
}

void MobModel::addAbilityName(const std::string& aName)
{
    mobAbilitiesNames.push_back(aName);
}

void MobModel::replaceAbilityWithName(const std::string& oldName, const std::string& newName)
{
    auto iter = std::find(mobAbilitiesNames.begin(), mobAbilitiesNames.end(), oldName);

    if (iter != mobAbilitiesNames.end())
    {
        *iter = newName;
    }
}

const list<string>& MobModel::getAbilitiesNames() const
{
    return mobAbilitiesNames;
}

std::array<int, GlobalConstants::resourceTypeCount> MobModel::getPrice() const
{
    return price;
}

int MobModel::getDamageArea() const
{
    return damageArea;
}

void MobModel::setDamageArea(int aDamageArea)
{
    damageArea = aDamageArea;
}

bool MobModel::getIsStunned() const
{
    return isStunned;
}

void MobModel::setIsStunned(bool aIsStunned)
{
    isStunned = aIsStunned;
}

