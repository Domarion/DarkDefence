#include "Mission.h"

Mission::Mission(const std::string& aCaption, const std::string& aDescription, const Reward& aReward)
    : caption(aCaption)
    , description(aDescription)
    , reward(aReward)
{
}

const std::string& Mission::getCaption() const
{
    return caption;
}

void Mission::setCaption(const std::string& aCaption)
{
    caption = aCaption;
}

const std::string& Mission::getDescription() const
{
    return description;
}

void Mission::setDescription(const std::string& aDescription)
{
    description = aDescription;
}

MissionStatuses Mission::checkStatus(Enums::GameStatuses aGameStatus)
{
    size_t goalCompleted = 0;
    for(auto goal = goals.begin(); goal != goals.end(); ++goal)
    {
        (*goal)->checkCondition(aGameStatus);
        if ((*goal)->getGoalStatus() == GoalStatuses::gFAILED)
        {
            missionStatus = MissionStatuses::mFAILED;
            return missionStatus;
        }

        if ((*goal)->getGoalStatus() == GoalStatuses::gCOMPLETED)
            ++goalCompleted;

    }

    missionStatus = (!goals.empty() && goalCompleted == goals.size())?
                    MissionStatuses::mCOMPLETED : MissionStatuses::mIN_PROGRESS;

    return missionStatus;
}

MissionStatuses Mission::getMissionStatus() const
{
    return missionStatus;
}

void Mission::setStatus(MissionStatuses aMissionStatus)
{
    missionStatus = aMissionStatus;
}

void Mission::addGoal(const std::shared_ptr<BasicGoal>& aGoal)
{
    goals.emplace_back(aGoal);
}

void Mission::setReward(const Reward& aReward)
{
    reward = aReward;
}

std::list<std::string> Mission::getGoalsFullDesc() const
{
    std::list<std::string> goalDescriptionList;
    for(const auto& goalPtr : goals)
    {
        if (!goalPtr)
        {
            continue;
        }

        std::string goalDescription = goalPtr->getDescription() + " " + std::to_string(goalPtr->getNeeded());
        goalDescriptionList.emplace_back(goalDescription);
    }

    return goalDescriptionList;
}

std::list<std::string> Mission::getGoalsNeeded() const
{
    std::list<std::string> goalNeededList;
    for(const auto& goalPtr : goals)
    {
        if (!goalPtr)
        {
            continue;
        }

        goalNeededList.emplace_back(std::to_string(goalPtr->getNeeded()));
    }

    return goalNeededList;
}

const std::list<std::shared_ptr<BasicGoal>>& Mission::getGoals() const
{
    return goals;
}

const Reward& Mission::getReward() const
{
    return reward;
}

void Mission::reset()
{
    missionStatus = MissionStatuses::mNOT_STARTED;
    description.clear();
    caption.clear();
}

bool Mission::isEmpty() const
{
    return caption.empty() && description.empty() && goals.empty();
}
