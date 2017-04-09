/*
 * Reward.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <cereal/access.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/utility.hpp>
using std::list;
using std::string;

class Reward
{
     friend class cereal::access;
     template <typename Archive>
     void serialize(Archive &ar, const unsigned int /*version*/)
     {
         ar(CEREAL_NVP(itemNames), CEREAL_NVP(goldCoins));
     }
public:
	Reward();
    explicit Reward(int coinsAmount);
	~Reward();
    void addItemName(string itemName);
    void setGoldCoins(int amount);
    int getGoldCoins() const;
    list<string> getFullDescription() const;
private:
    list<string> itemNames;
    int goldCoins;
};

