#include "ResourceGoal.h"

ResourceGoal::ResourceGoal()
    :resourceType(Enums::ResourceTypes::WOOD)
{

}

ResourceGoal::ResourceGoal(std::string aDescription, int controlNumber, Enums::ResourceTypes aResourceType)
    :BasicGoal(aDescription, controlNumber), resourceType(aResourceType)
{

}

void ResourceGoal::setResourceType(Enums::ResourceTypes resType)
{
    resourceType = resType;
}

bool ResourceGoal::checkCondition()
{
    if (BasicGoal::checkCondition() == false)
        return false;

    current = GameModel::getInstance()->getResourcesModel()->getResourceAmountFromIndex(static_cast<int>(resourceType));

    if (current >= needed)
        goalStatus = GoalStatuses::gCOMPLETED;
    else
        goalStatus = GoalStatuses::gIN_PROGRESS;

    return true;
}

Enums::ResourceTypes ResourceGoal::getResourceType()
{
    return resourceType;
}
