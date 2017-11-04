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
#include "GlobalConstants.h"
#include <functional>

using std::string;
using std::pair;

class DestructibleObject
{
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar(
            CEREAL_NVP(name),
            CEREAL_NVP(tag),
            CEREAL_NVP(maximumHealth),
            cereal::make_nvp("protection", attackProtection));

        currentHealth = maximumHealth.first;
        Alive = true;
    }

public:

    DestructibleObject() = default;
    DestructibleObject(
        const std::string& aName,
        const std::string& aTag,
        int aMaxHealth,
        std::array<int, GlobalConstants::damageTypeCount>& aProtection);
    DestructibleObject(const DestructibleObject& aRight);
    DestructibleObject& operator =(const DestructibleObject& aRight);
    virtual ~DestructibleObject() = default;

    const std::array<pair<int, int>, GlobalConstants::damageTypeCount>& getAttackProtection() const;
    const string& getName() const;
    void setName(const string& aName);
    const string& getTag() const;
    void setTag(const string& aTag);
    bool IsAlive() const;

    bool receiveDamage(const std::array<int, GlobalConstants::damageTypeCount>& aDamage);
    bool receiveDamageOneType(size_t aDamageType, int aDamage);
    bool addHealth(int aAmount);
    void setProtectionModifier(int aModifier);
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
    int currentHealth = 0;
    pair<int, int> maximumHealth {0, 0};
    bool Alive = true;
    std::array<pair<int, int>, GlobalConstants::damageTypeCount> attackProtection{};

    std::function<void(int, int)> connectedMethod;
};

