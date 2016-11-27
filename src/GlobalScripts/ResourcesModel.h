/*
 * ResourcesModel.h
 *
 *  Created on: 15 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "ResourceInfo.h"
#include "../GlobalConstants.h"
#include <array>

class ResourcesModel
{
public:
    using PriceArray = std::array<int, GlobalConstants::resourceTypeCount>;
    ResourcesModel() = default;
    ~ResourcesModel() = default;
    std::string getResourceNameFromIndex(size_t index);
    std::string printResourceFromIndex(size_t index);

    bool canBuy(PriceArray costarray);
    void addResources(PriceArray costarray);
    void removeResources(PriceArray costarray);
    int getResourceAmountFromIndex(int resourceType);
	bool haveEnoughResource(int resourceType, int amount);
	bool addResource(int resourceType, int amount);
	bool removeResource(int resourceType, int amount);
	void increaseLimit(int resourceType, int amount);
	void decreaseLimit(int resourceType, int amount);
    void loadFromFile(std::string filename);
private:
    std::array<ResourceInfo, GlobalConstants::resourceTypeCount> resourceTypes;
};
