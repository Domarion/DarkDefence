/*
 * ResourcesModel.cpp
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "ResourcesModel.h"
#include <fstream>
#include "../Utility/textfilefunctions.h"
#include <sstream>

using std::stringstream;

const std::string& ResourcesModel::getResourceNameFromIndex(size_t index)
{
	return resourceTypes[index].getCaption();
}

const std::string& ResourcesModel::getResourceNameFromType(Enums::ResourceTypes aResourceType)
{
    return getResourceNameFromIndex(Enums::toIntegralType(aResourceType));
}

std::string ResourcesModel::printResourceFromIndex(size_t index)
{
	return resourceTypes[index].printToString();
}

bool ResourcesModel::canBuy(PriceArray costarray)
{
    for(size_t i = 0; i < GlobalConstants::resourceTypeCount; ++i)
		if (!haveEnoughResource(i, costarray[i]))
			return false;
	return true;
}

void ResourcesModel::addResources(PriceArray costarray)
{
    for (size_t i = 0; i < GlobalConstants::resourceTypeCount; ++i)
		resourceTypes[i].addResource(costarray[i]);
}

void ResourcesModel::removeResources(PriceArray costarray)
{
    for (size_t i = 0; i < GlobalConstants::resourceTypeCount; ++i)
        resourceTypes[i].removeResource(costarray[i]);
}

int ResourcesModel::getResourceAmountFromIndex(size_t resourceType)
{
    return resourceTypes[resourceType].getCurrentAmount();
}

bool ResourcesModel::haveEnoughResource(size_t resourceType, int amount)
{
	return resourceTypes[resourceType].getCurrentAmount() >= amount;
}

bool ResourcesModel::addResource(size_t resourceType, int amount)
{
	return resourceTypes[resourceType].addResource(amount);
}

bool ResourcesModel::removeResource(size_t resourceType, int amount)
{
	return resourceTypes[resourceType].removeResource(amount);
}

void ResourcesModel::increaseLimit(int resourceType, int amount)
{
	resourceTypes[resourceType].increaseLimit(amount);
}

void ResourcesModel::decreaseLimit(int resourceType, int amount)
{
    resourceTypes[resourceType].decreaseLimit(amount);
}

void ResourcesModel::loadFromFile(const std::string& aFilename)
{
    string textString;
    androidText::loadTextFileToString(aFilename, textString);

    if (!textString.empty())
    {
        stringstream somestream(textString);

        for(size_t i = 0; i != GlobalConstants::resourceTypeCount; ++i)
        {
            int amount = 0;
            int limit = 0;
            somestream  >> amount >> limit;
            resourceTypes[i].setLimit(limit);
            resourceTypes[i].setCurrentAmount(amount);
        }
    }
}

void ResourcesModel::loadResourceNamesFromFile(const std::string& aFilename)
{
    string textString;
    androidText::loadTextFileToString(aFilename, textString);

    if (!textString.empty())
    {
        stringstream somestream(textString);

        for(size_t i = 0; i < GlobalConstants::resourceTypeCount; ++i)
        {
            std::string caption;
            somestream >> caption;
            resourceTypes[i].setCaption(caption);
        }
    }
}
