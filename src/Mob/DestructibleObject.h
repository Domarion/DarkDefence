/*
 * DestructibleObject.h
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once


#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/version.hpp>

#include <utility>
using std::pair;
#include <string>
using std::string;

//#include "../Utility/Subject.h"
#include <functional>
class DestructibleObject//: public Subject
{
	friend class boost::serialization::access;
		template <typename Archive>
          void serialize(Archive &ar, const unsigned int /*version*/)
		{
			ar & BOOST_SERIALIZATION_NVP(name);
			ar & BOOST_SERIALIZATION_NVP(tag);
			ar & BOOST_SERIALIZATION_NVP(maximumHealth);
            currentHealth = maximumHealth.first;
			//for (int i = 0; i < DestructibleObject::damageTypesCount; ++i)

            ar & boost::serialization::make_nvp("attack", attackProtection);

            Alive = true;
			//ar & attackProtection;
		}
public:
	const static int damageTypesCount = 4;
	DestructibleObject();
	DestructibleObject(string aName, string aTag, int aMaxHealth, int aProtection[]);
    DestructibleObject(const DestructibleObject& right);

    virtual ~DestructibleObject();
	const pair<int, int>& getAttackProtection() const;
	const string& getName() const;
	void setName(const string& name);
	const string& getTag() const;
	void setTag(const string& tag);
	bool IsAlive() const;

    bool receiveDamage(int* damage);
    bool receiveDamageOneType(int damage_type, int damage);
    bool addHealth(int amount);
    void setProtectionModifier(int modifier);
    int getProtectionModifier() const;

	int getMaximumHealth() const;
	void setMaximumHealth(int hp);
    int getCurrentHealth() const;

    void connectMethod(std::function<void(int, int)> handler);

protected:
    bool changeHealth(int amount);
	void setCurrentHealth(int hp);
	void setIsAlive(bool isAlive);
	string name;
	string tag;
	bool Alive;
	pair<int, int> maximumHealth;
	int currentHealth;
	pair<int, int> attackProtection[damageTypesCount];


    std::function<void(int, int)> connectedMethod;
};

