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
    void serialize(Archive &ar)
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
            CEREAL_NVP(price)
           );

        reloadTime = reloadTimeMaximum.first + reloadTimeMaximum.second;

	}


public:
	MobModel();
    MobModel(string aName,
             string aTag,
             int aMaxHealth,
             int aProtection[],
             int damage[],
             double distance,
             double speed,
             double aReloadTime,
             int aDamageArea,
             list<EnemyInfo> enemiesTags);

    virtual ~MobModel() = default;

	MobModel(const MobModel& right);
	const pair<double, double>& getAttackDistance() const;
	void setAttackDistance(const pair<double, double>& attackDistance);

    int* getAttackDamage();

	const pair<double, double>& getMoveSpeed() const;
	void setMoveSpeed(const pair<double, double>& moveSpeed);
    const list<EnemyInfo> &getEnemyTags() const;
	bool checkDistance(int distanceSqr);

    void setAttackDamageModifier(size_t index, int modifier);
    int getAttackDamageModifier(size_t index);

    void setAttackDamageWithIndex(size_t index, int value);
    int getAttackDamageWithIndex(int index);


    void setMoveSpeedModifier(double modifier);
    double getMoveSpeedModifier() const;


    void setAttackDistanceModifier(double modifier);
    double getAttackDistanceModifier() const;

	void reload();
	double getReloadTime() const;
	void setReloadTime(double reloadTime);


    void setReloadTimeMaximum(double reloadTimeMax);

    double getReloadTimeModifier() const;
    void setReloadTimeModifier(double modifier);

    bool isMobVisible() const;
    void setMobVisiblity(bool flag);
    void setAbilitiesNames(list<string> abNames);
    void addAbilityName(string name);
    void replaceAbilityWithName(const string& oldName, const string& newName);
    list<string>& getAbilitiesNames();

    std::array<int, GlobalConstants::resourceTypeCount> getPrice();
    int getDamageArea() const;
    void setDamageArea(int value);
    bool getIsStunned() const;
    void setIsStunned(bool value);

private:

    std::array<pair<int, int>, GlobalConstants::damageTypeCount> attackDamage;
	pair<double, double> attackDistance;
	pair<double, double> moveSpeed;

	pair<double, double> reloadTimeMaximum;
    double reloadTime;
    int damageArea;
    list<EnemyInfo> enemiesInfo;
    bool isVisible;
    bool isStunned;
	//int x, y;

    list<string> mobAbilitiesNames;
    std::array<int, GlobalConstants::resourceTypeCount> price;

};


