/*
 * Reward.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "Reward.h"

Reward::Reward()
{
	// TODO Auto-generated constructor stub

}

Reward::~Reward()
{
    // TODO Auto-generated destructor stub
}

void Reward::addItemName(string itemName)
{
    itemNames.push_back(itemName);
}

void Reward::setGoldCoins(int amount)
{
    goldCoins = amount;
}

int Reward::getGoldCoins() const
{
    return goldCoins;
}

list<string> Reward::getFullDescription()
{
    list<string> someList;
    someList.insert(someList.end(), itemNames.begin(), itemNames.end());
   // string s = "GoldCoins " + std::to_string(goldCoins);
    //someList.push_back(s);
    return someList;
}

