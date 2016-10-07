/*
 * BasicGoal.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "BasicGoal.h"
#include <string>
#include "../GlobalScripts/GameModel.h"

BasicGoal::BasicGoal()
    :current(0), needed(0), description(), goalStatus(GoalStatuses::gIN_PROGRESS)
{
	// TODO Auto-generated constructor stub

}

BasicGoal::BasicGoal(std::string aDescription, int controlNumber)
    :current(0), needed(controlNumber), description(aDescription), goalStatus(GoalStatuses::gIN_PROGRESS)
{

}

BasicGoal::~BasicGoal()
{
	// TODO Auto-generated destructor stub
}

int BasicGoal::getCurrent() const
{
	return current;
}

void BasicGoal::setCurrent(int value)
{
	current = value > 0 ? value : 0;
}

int BasicGoal::getNeeded() const
{
	return needed;
}

void BasicGoal::setNeeded(int value)
{
	needed = value > 0 ? value : 0;
}

std::string BasicGoal::getDescription() const
{
	return description;
}

void BasicGoal::setDescription(std::string value)
{
	description = value;
}

GoalStatuses BasicGoal::getGoalStatus() const
{
	return goalStatus;
}

void BasicGoal::setGoalStatus(GoalStatuses value)
{
    goalStatus = value;
}

bool BasicGoal::checkCondition()
{
    if (GameModel::getInstance()->getGameStatus() == Enums::GameStatuses::gsLOST)
    {
        goalStatus = GoalStatuses::gFAILED;
        return false;
    }


    return true;
}
