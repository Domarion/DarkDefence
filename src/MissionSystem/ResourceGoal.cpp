#include "ResourceGoal.h"

ResourceGoal::ResourceGoal(
    const std::string& aDescription,
    int aControlNumber,
    Enums::ResourceTypes aResourceType)
    : BasicGoal(aDescription, aControlNumber)
    , resourceType(aResourceType)
{
}

void ResourceGoal::setResourceModel(const std::shared_ptr<ResourcesModel>& aResourceModel)
{
    resourceModel = aResourceModel;
}

void ResourceGoal::setResourceType(Enums::ResourceTypes aResType)
{
    resourceType = aResType;
}

bool ResourceGoal::checkCondition(Enums::GameStatuses aGameStatus)
{
    if (!BasicGoal::checkCondition(aGameStatus))
        return false;

    current = getResourceAmount();

    goalStatus = current >= needed ? GoalStatuses::gCOMPLETED : GoalStatuses::gIN_PROGRESS;

    return true;
}

Enums::ResourceTypes ResourceGoal::getResourceType() const
{
    return resourceType;
}

int ResourceGoal::getResourceAmount() const // TODO какой-то хардкод
{
    return 0;//resourceModel->getResourceAmountFromIndex(static_cast<int>(resourceType));
}
