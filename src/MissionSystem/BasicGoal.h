/*
 * BasicGoal.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <string>

enum GoalStatuses
{
	gIN_PROGRESS,
	gCOMPLETED,
	gFAILED
};

class BasicGoal
{
public:
	BasicGoal();
	virtual ~BasicGoal();
	int getCurrent() const;
	void setCurrent(int value);
	int getNeeded() const;
	void setNeeded(int value);
	std::string getDescription() const;
	void setDescription(std::string value);
	GoalStatuses getGoalStatus() const;
	void setGoalStatus(GoalStatuses value);

private:
	int current;
	int needed;
	std::string description;
	GoalStatuses goalStatus;
};

