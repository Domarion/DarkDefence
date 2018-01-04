#include "ResourceGoal.h"
#include <cassert>
#include "../GlobalScripts/GameModel.h"

ResourceGoal::ResourceGoal(
    const std::string& aDescription,
    int aControlNumber,
    Enums::ResourceTypes aResourceType)
    : BasicGoal(aDescription, aControlNumber)
    , mResourceType(aResourceType)
{
}

void ResourceGoal::setResourceModel(const std::shared_ptr<ResourcesModel>& aResourceModel)
{
    mResourceModel = aResourceModel;
}

void ResourceGoal::setResourceType(Enums::ResourceTypes aResType)
{
    mResourceType = aResType;
}

bool ResourceGoal::checkCondition(Enums::GameStatuses aGameStatus)
{
    if (!BasicGoal::checkCondition(aGameStatus))
    {
        return false;
    }

    current = getResourceAmount();

    if (current < 0)
    {
        return false;
    }

    goalStatus = current >= needed ? GoalStatuses::gCOMPLETED : GoalStatuses::gIN_PROGRESS;

    return true;
}

Enums::ResourceTypes ResourceGoal::getResourceType() const
{
    return mResourceType;
}

int ResourceGoal::getResourceAmount() const
{
    return GameModel::getInstance()->getResourcesModel()->getResourceAmountFromType(mResourceType);
}
