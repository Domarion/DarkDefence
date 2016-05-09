/*
 * MobModel.h
 *
 *  Created on: 9 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "DestructibleObject.h"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/list.hpp>
using std::pair;
#include <list>
using std::list;



class MobModel: public DestructibleObject
{
	friend class boost::serialization::access;
	template <typename Archive>
	  void serialize(Archive &ar, const unsigned int version)
	{

		//ar.template register_type<MobModel>();
		ar & boost::serialization::make_nvp("DestructibleObject", (boost::serialization::base_object<DestructibleObject>(*this)));
		//ar & attackDamage;

		ar & BOOST_SERIALIZATION_NVP(attackDamage);
		ar & BOOST_SERIALIZATION_NVP(attackDistance);
		ar & BOOST_SERIALIZATION_NVP(moveSpeed);
        ar & BOOST_SERIALIZATION_NVP(reloadTimeMaximum);
		ar & BOOST_SERIALIZATION_NVP(enemyTags);
        ar & boost::serialization::make_nvp("Abilities", mobAbilitiesNames);
        reloadTime = reloadTimeMaximum.first + reloadTimeMaximum.second;
	}


public:
	MobModel();
	MobModel(string aName, string aTag,
			int aMaxHealth, int aProtection[], int damage[], double distance, double speed, list<string> enemiesTags);
	virtual ~MobModel();

	MobModel(const MobModel& right);
	const pair<double, double>& getAttackDistance() const;
	void setAttackDistance(const pair<double, double>& attackDistance);

    int* getAttackDamage();

	const pair<double, double>& getMoveSpeed() const;
	void setMoveSpeed(const pair<double, double>& moveSpeed);
	const list<string>& getEnemyTags() const;
	bool checkDistance(int distanceSqr);

    void setAttackDamageModifier(int index, int modifier);
    int getAttackDamageModifier(int index);

    void setAttackDamageWithIndex(int index, int value);
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



    void setAbilitiesNames(list<string> abNames);
    list<string>& getAbilitiesNames();

private:

	pair<int, int> attackDamage[DestructibleObject::damageTypesCount];
	pair<double, double> attackDistance;
	pair<double, double> moveSpeed;
	list<string> enemyTags;
	pair<double, double> reloadTimeMaximum;
	double reloadTime;
	//int x, y;

    list<string> mobAbilitiesNames;


};


