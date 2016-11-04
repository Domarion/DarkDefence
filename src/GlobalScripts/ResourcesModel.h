/*
 * ResourcesModel.h
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "ResourceInfo.h"

class ResourcesModel
{
public:
    static const int resourceTypeCount = 3;
	ResourcesModel();
	~ResourcesModel();
    std::string getResourceNameFromIndex(size_t index);
    std::string printResourceFromIndex(size_t index);

	bool canBuy(int costarray[]);
	void addResources(int costarray[]);
	void removeResources(int costarray[]);
    int getResourceAmountFromIndex(int resourceType);
	bool haveEnoughResource(int resourceType, int amount);
	bool addResource(int resourceType, int amount);
	bool removeResource(int resourceType, int amount);
	void increaseLimit(int resourceType, int amount);
	void decreaseLimit(int resourceType, int amount);
    void loadFromFile(std::string filename);
private:
	ResourceInfo resourceTypes[resourceTypeCount];
};
