#include <cassert>

#include "ResourceInfo.h"

bool ResourceInfo::addResource(int aAmount)
{
    if (currentAmount == limit || aAmount > limit)
    {
        return false;
    }

    currentAmount += aAmount;

	if (currentAmount > limit)
		currentAmount = limit;

	return true;
}

bool ResourceInfo::removeResource(int aAmount)
{
    if (currentAmount < aAmount)
		return false;

    currentAmount -= aAmount;
	return true;
}

void ResourceInfo::increaseLimit(int aAmount)
{
    assert(aAmount >= 0 && "increaseLimit: Amount < 0");
    limit += aAmount;
}

void ResourceInfo::decreaseLimit(int aAmount)
{
    if (limit <= aAmount)
    {
		limit = 0;
        return;
    }

    limit -= aAmount;
}

const std::string& ResourceInfo::getCaption() const
{
	return caption;
}

void ResourceInfo::setCaption(const std::string& aCaption)
{
    caption = aCaption;
}

int ResourceInfo::getCurrentAmount() const
{
	return currentAmount;
}

void ResourceInfo::setCurrentAmount(int aCurrentAmount)
{
    currentAmount = aCurrentAmount > 0 ? aCurrentAmount : 0;
}

int ResourceInfo::getLimit() const
{
	return limit;
}

void ResourceInfo::setLimit(int aLimitAmount)
{
    limit = aLimitAmount > 0 ? aLimitAmount : 0;
}

std::string ResourceInfo::printToString() const
{
    return std::to_string(getCurrentAmount());
}
