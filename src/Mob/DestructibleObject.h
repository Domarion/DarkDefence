/*
 * DestructibleObject.h
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <cereal/access.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/array.hpp>

using std::string;

#include <functional>
using std::pair;

class DestructibleObject
{
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int /*version*/)
    {
        ar(CEREAL_NVP(name), CEREAL_NVP(tag), CEREAL_NVP(maximumHealth), cereal::make_nvp("protection", attackProtection));

        currentHealth = maximumHealth.first;
        Alive = true;
    }
public:
	const static int damageTypesCount = 4;
	DestructibleObject();
	DestructibleObject(string aName, string aTag, int aMaxHealth, int aProtection[]);
    DestructibleObject(const DestructibleObject& right);

    virtual ~DestructibleObject();
    std::array<pair<int, int>, damageTypesCount> getAttackProtection() const;
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
    int currentHealth;
	pair<int, int> maximumHealth;
    std::array<pair<int, int>, damageTypesCount> attackProtection;


    std::function<void(int, int)> connectedMethod;
};

