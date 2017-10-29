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
#include "Enums.h"

class ResourcesModel
{
public:
    using PriceArray = std::array<int, GlobalConstants::resourceTypeCount>;
    ResourcesModel() = default;
    ~ResourcesModel() = default;
    const std::string& getResourceNameFromIndex(size_t index);
    const std::string& getResourceNameFromType(Enums::ResourceTypes aResourceType);
    std::string printResourceFromIndex(size_t index);

    bool canBuy(PriceArray costarray);
    void addResources(PriceArray costarray);
    void removeResources(PriceArray costarray);
    int getResourceAmountFromIndex(size_t resourceType);
    bool haveEnoughResource(size_t resourceType, int amount);
    bool addResource(size_t resourceType, int amount);
    bool addResource(Enums::ResourceTypes aResourceType, int aAmount);

    bool removeResource(size_t resourceType, int amount);
	void increaseLimit(int resourceType, int amount);
	void decreaseLimit(int resourceType, int amount);
    void loadFromFile(const std::string& aFilename);
    void loadResourceNamesFromFile(const std::string& aFilename);
private:
    std::array<ResourceInfo, GlobalConstants::resourceTypeCount> resourceTypes;
};
