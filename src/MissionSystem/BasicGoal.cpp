#include "BasicGoal.h"

BasicGoal::BasicGoal(const std::string& aDescription, int aControlNumber)
    : description(aDescription)
    , needed(aControlNumber)
{
}

int BasicGoal::getCurrent() const
{
	return current;
}

void BasicGoal::setCurrent(int aCurrent)
{
    current = aCurrent > 0 ? aCurrent : 0;
}

int BasicGoal::getNeeded() const
{
	return needed;
}

void BasicGoal::setNeeded(int aNeeded)
{
    needed = aNeeded > 0 ? aNeeded : 0;
}

std::string BasicGoal::getDescription() const
{
	return description;
}

void BasicGoal::setDescription(const std::string& aDescription)
{
    description = aDescription;
}

GoalStatuses BasicGoal::getGoalStatus() const
{
	return goalStatus;
}

void BasicGoal::setGoalStatus(GoalStatuses aGoalStatus)
{
    goalStatus = aGoalStatus;
}

bool BasicGoal::checkCondition(Enums::GameStatuses aGameStatus)
{
    if (aGameStatus == Enums::GameStatuses::gsLOST)
    {
        goalStatus = GoalStatuses::gFAILED;
        return false;
    }

    return true;
}
