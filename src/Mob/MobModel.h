/*
 * MobModel.h
 *
 *  Created on: 9 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "DestructibleObject.h"
#include "EnemyInfo.h"
#include <cereal/types/base_class.hpp>
#include <cereal/types/list.hpp>
#include "../GlobalConstants.h"

using std::pair;
using std::list;

class MobModel: public DestructibleObject
{
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive& ar)
    {
        ar(
            cereal::base_class<DestructibleObject>(this),
            CEREAL_NVP(attackDamage),
            CEREAL_NVP(attackDistance),
            CEREAL_NVP(moveSpeed),
            CEREAL_NVP(reloadTimeMaximum),
            CEREAL_NVP(damageArea),
            cereal::make_nvp("enemyTags", enemiesInfo),
            cereal::make_nvp("Abilities", mobAbilitiesNames),
            CEREAL_NVP(price),
            cereal::make_nvp("ArrowName", arrowName)
        );
    }

public:

    MobModel() = default;
    MobModel(
        const std::string& aName,
        const std::string& aTag,
        int aMaxHealth,
        std::array<int, GlobalConstants::damageTypeCount>& aProtection,
        std::array<int, GlobalConstants::damageTypeCount>& aDamage,
        double aDistance,
        double aSpeed,
        double aReloadTime,
        int aDamageArea,
        list<EnemyInfo> aEnemiesTags,
        const std::string& aArrowName);

    virtual ~MobModel() = default;

    MobModel(const MobModel& right);

    const std::string& getArrowName() const;
    void setArrowName(const std::string& aArrowName);

    const pair<double, double>& getAttackDistance() const;
    void setAttackDistance(const pair<double, double>& attackDistance);

    std::array<int, GlobalConstants::damageTypeCount> getAttackDamage();

    const pair<double, double>& getMoveSpeed() const;
    void setMoveSpeed(const pair<double, double>& moveSpeed);
    const list<EnemyInfo>& getEnemyTags() const;
    bool checkDistance(int distanceSqr);

    void setAttackDamageModifier(size_t index, int modifier);
    int getAttackDamageModifier(size_t index);

    void setAttackDamageWithIndex(size_t index, int value);
    int getAttackDamageWithIndex(size_t index);


    void setMoveSpeedModifier(double modifier);
    double getMoveSpeedModifier() const;


    void setAttackDistanceModifier(double modifier);
    double getAttackDistanceModifier() const;

    void reload();
    double getReloadTimeCurrent() const;
    void setReloadTimeCurrent(double reloadTime);

    void setReloadTimeMaximumBase(double reloadTimeMax);

    double getReloadTimeMaximumModifier() const;
    void setReloadTimeMaximumModifier(double modifier);

    double getReloadTimeMaximumBase() const;

    bool IsReloadingInProgress() const;
    void ProcessReloadStep(double aTimeStep);
    bool isMobVisible() const;
    void setMobVisiblity(bool aIsVisible);
    void setAbilitiesNames(const list<std::string>& aAbilityNamesList);
    void addAbilityName(const std::string& aName);
    void replaceAbilityWithName(const string& oldName, const string& newName);
    const list<std::string>& getAbilitiesNames() const;

    std::array<int, GlobalConstants::resourceTypeCount> getPrice() const;
    int getDamageArea() const;
    void setDamageArea(int aDamageArea);
    bool getIsStunned() const;
    void setIsStunned(bool aIsStunned);

private:

    std::array<pair<int, int>, GlobalConstants::damageTypeCount> attackDamage = {};
    pair<double, double> attackDistance{};
    pair<double, double> moveSpeed{};

    pair<double, double> reloadTimeMaximum{};
    double reloadTime = 0;
    int damageArea = 0;
    list<EnemyInfo> enemiesInfo;
    std::string arrowName;
    bool isVisible = true;
    bool isStunned = false;

    list<string> mobAbilitiesNames;
    std::array<int, GlobalConstants::resourceTypeCount> price = {};
};


