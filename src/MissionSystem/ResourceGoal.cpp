#include "ResourceGoal.h"

ResourceGoal::ResourceGoal()
    :resourceType(Enums::ResourceTypes::GOLD)
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

    current = GameModel::getInstance()->getResourcesModel()->getResourceAmountFromIndex(resourceType);

    if (current >= needed)
        goalStatus = GoalStatuses::gCOMPLETED;
    else
        goalStatus = GoalStatuses::gIN_PROGRESS;

    return true;
}
