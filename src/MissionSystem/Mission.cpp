/*
 * Mission.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "Mission.h"

Mission::Mission()
    :missionStatus(mNOT_STARTED)
{
	// TODO Auto-generated constructor stub

}

Mission::~Mission()
{
	// TODO Auto-generated destructor stub
}

std::string Mission::getCaption() const
{
	return caption;
}

void Mission::setCaption(std::string value)
{
	caption = value;
}

std::string Mission::getDescription() const
{
	return description;
}

void Mission::setDescription(std::string value)
{
    description = value;
}

MissionStatuses Mission::checkStatus()
{
    int goalCompleted = 0;
    for(auto goal = goals.begin(); goal != goals.end(); ++goal)
    {
        (*goal)->checkCondition();
        if ((*goal)->getGoalStatus() == gFAILED)
        {
            missionStatus = mFAILED;
            return missionStatus;
        }

        if ((*goal)->getGoalStatus() == gCOMPLETED)
            ++goalCompleted;

    }

    missionStatus = (goalCompleted == goals.size() && goals.size() > 0)? mCOMPLETED : mIN_PROGRESS;

    return missionStatus;
}

MissionStatuses Mission::getStatus() const
{
    return missionStatus;
}

void Mission::setStatus(MissionStatuses value)
{
    missionStatus = value;
}

void Mission::addGoal(BasicGoal *goal)
{
    goals.push_back(goal);
}

void Mission::setReward(const Reward &someReward)
{
    reward = someReward;
}

std::list<std::string> Mission::getGoalsFullDesc()
{
    list<std::string> someList;
    for(auto goalPtr = goals.begin(); goalPtr != goals.end(); ++goalPtr)
    {
        std::string s = (*goalPtr)->getDescription() + " " + std::to_string((*goalPtr)->getNeeded());
        someList.push_back(s);
    }

    return someList;
}

std::list<string> Mission::getGoalsNeeded()
{
    list<std::string> someList;
    for(auto goalPtr = goals.begin(); goalPtr != goals.end(); ++goalPtr)
    {
        std::string s = std::to_string((*goalPtr)->getNeeded());
        someList.push_back(s);
    }

    return someList;
}

std::list<BasicGoal *> &Mission::getGoals()
{
    return goals;
}

Reward &Mission::getReward()
{
    return reward;
}
