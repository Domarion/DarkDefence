#include "Reward.h"

Reward::Reward(int aCoinsAmount)
    : mCoinsAmount(aCoinsAmount)
{
}

void Reward::addItemName(const std::string& aItemName)
{
    mItemNames.emplace_back(aItemName);
}

void Reward::setGoldCoins(int aCoinsAmount)
{
    mCoinsAmount = aCoinsAmount;
}

int Reward::getGoldCoins() const
{
    return mCoinsAmount;
}

const std::list<std::string>& Reward::getFullDescription() const
{
    return mItemNames;
}

