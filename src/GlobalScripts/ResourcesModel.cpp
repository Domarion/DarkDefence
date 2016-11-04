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

ResourcesModel::ResourcesModel()
{
	// TODO Auto-generated constructor stub

}

ResourcesModel::~ResourcesModel()
{
	// TODO Auto-generated destructor stub
}

std::string ResourcesModel::getResourceNameFromIndex(size_t index)
{
	return resourceTypes[index].getCaption();
}

std::string ResourcesModel::printResourceFromIndex(size_t index)
{
	return resourceTypes[index].printToString();
}

bool ResourcesModel::canBuy(int costarray[])
{
	for(int i = 0; i < ResourcesModel::resourceTypeCount; ++i)
		if (!haveEnoughResource(i, costarray[i]))
			return false;
	return true;
}

void ResourcesModel::addResources(int costarray[])
{
	for (int i = 0; i < ResourcesModel::resourceTypeCount; ++i)
		resourceTypes[i].addResource(costarray[i]);
}

void ResourcesModel::removeResources(int costarray[])
{
	for (int i = 0; i < ResourcesModel::resourceTypeCount; ++i)
        resourceTypes[i].removeResource(costarray[i]);
}

int ResourcesModel::getResourceAmountFromIndex(int resourceType)
{
    return resourceTypes[resourceType].getCurrentAmount();
}

bool ResourcesModel::haveEnoughResource(int resourceType, int amount)
{
	return resourceTypes[resourceType].getCurrentAmount() >= amount;
}

bool ResourcesModel::addResource(int resourceType, int amount)
{
	return resourceTypes[resourceType].addResource(amount);
}

bool ResourcesModel::removeResource(int resourceType, int amount)
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

void ResourcesModel::loadFromFile(std::string filename)
{
    string textString;
    androidText::loadTextFileToString(filename, textString);


    if (!textString.empty())
    {
        stringstream somestream(textString);

        for(int i = 0; i != ResourcesModel::resourceTypeCount; ++i)
        {
            std::string s;
            int amount;
            int limit;
            somestream >> s >> amount >> limit;
            resourceTypes[i].setCaption(s);
            resourceTypes[i].setLimit(limit);
            resourceTypes[i].setCurrentAmount(amount);
        }
    }
}
