/*
 * ResourceInfo.cpp
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "ResourceInfo.h"
#include <sstream>
ResourceInfo::ResourceInfo()
{
	// TODO Auto-generated constructor stub

}

ResourceInfo::~ResourceInfo()
{
	// TODO Auto-generated destructor stub
}

bool ResourceInfo::addResource(int amount)
{
	if (currentAmount == limit || amount > limit)
        return false;

	currentAmount += amount;

	if (currentAmount > limit)
		currentAmount = limit;

	return true;
}

bool ResourceInfo::removeResource(int amount)
{
	if (currentAmount < amount)
		return false;

	currentAmount -= amount;
	return true;
}

void ResourceInfo::increaseLimit(int amount)
{
	limit += amount;
}

void ResourceInfo::decreaseLimit(int amount)
{
	if (limit < amount)
		limit = 0;
	else
		limit -= amount;
}

const std::string& ResourceInfo::getCaption() const
{
	return caption;
}

void ResourceInfo::setCaption(const std::string& caption)
{
	this->caption = caption;
}

int ResourceInfo::getCurrentAmount() const
{
	return currentAmount;
}

void ResourceInfo::setCurrentAmount(int value)
{
	if (value > 0)
		currentAmount = value;
	else
		currentAmount = 0;
}

int ResourceInfo::getLimit() const
{
	return limit;
}

void ResourceInfo::setLimit(int value)
{
	if (value > 0)
		limit = value;
	else
		limit = 0;
}

std::string ResourceInfo::printToString() const
{
	std::ostringstream outStringStream;
    outStringStream << getCurrentAmount() << '/' << getLimit();
	return outStringStream.str();
}
