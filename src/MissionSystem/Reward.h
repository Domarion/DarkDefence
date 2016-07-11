/*
 * Reward.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/version.hpp>
#include <list>
using std::list;
#include <string>
using std::string;

class Reward
{
     friend class boost::serialization::access;
     template <typename Archive>
     void serialize(Archive &ar, const unsigned int version)
     {
         ar & BOOST_SERIALIZATION_NVP(itemNames);
         ar & BOOST_SERIALIZATION_NVP(goldCoins);
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

