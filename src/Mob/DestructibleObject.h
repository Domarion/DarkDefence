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
    const static size_t damageTypesCount = 4;
    DestructibleObject() = default;
	DestructibleObject(string aName, string aTag, int aMaxHealth, int aProtection[]);
    DestructibleObject(const DestructibleObject& aRight);
    DestructibleObject& operator =(const DestructibleObject& aRight);

    virtual ~DestructibleObject() = default;
    std::array<pair<int, int>, damageTypesCount> getAttackProtection() const;
	const string& getName() const;
    void setName(const string& aName);
	const string& getTag() const;
    void setTag(const string& aTag);
	bool IsAlive() const;

    bool receiveDamage(int* damage);
    bool receiveDamageOneType(size_t damage_type, int damage);
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
    void setIsAlive(bool aAlive);
	string name;
	string tag;
    bool Alive = true;
    int currentHealth = 0;
    pair<int, int> maximumHealth {0, 0};
    std::array<pair<int, int>, damageTypesCount> attackProtection;


    std::function<void(int, int)> connectedMethod;
};

