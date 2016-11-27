#include "ResourceGoal.h"

ResourceGoal::ResourceGoal()
    : BasicGoal()
    , resourceType(Enums::ResourceTypes::WOOD)
{

}

ResourceGoal::ResourceGoal(std::string aDescription, int controlNumber,
                           Enums::ResourceTypes aResourceType, std::shared_ptr<ResourcesModel> aResourceModel)
    :BasicGoal(aDescription, controlNumber), resourceType(aResourceType), resourceModel(aResourceModel)
{

}

void ResourceGoal::setResourceModel(std::shared_ptr<ResourcesModel> aResourceModel)
{
    resourceModel = aResourceModel;
}

void ResourceGoal::setResourceType(Enums::ResourceTypes resType)
{
    resourceType = resType;
}

bool ResourceGoal::checkCondition(Enums::GameStatuses aGameStatus)
{
    if (BasicGoal::checkCondition(aGameStatus) == false)
        return false;



    current = getResourceAmount();

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

int ResourceGoal::getResourceAmount()
{
    return 0;//resourceModel->getResourceAmountFromIndex(static_cast<int>(resourceType));
}
