/*
 * BasicGoal.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <cereal/access.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/utility.hpp>
#include "Enums.h"
enum class GoalStatuses
{
	gIN_PROGRESS,
	gCOMPLETED,
	gFAILED
};

class BasicGoal
{
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive &ar, const unsigned int /*version*/)
    {
        ar(description, goalStatus, needed);
    }
public:
	BasicGoal();
    BasicGoal(std::string aDescription, int controlNumber);
	virtual ~BasicGoal();
	int getCurrent() const;
	void setCurrent(int value);
	int getNeeded() const;
	void setNeeded(int value);
	std::string getDescription() const;
	void setDescription(std::string value);
	GoalStatuses getGoalStatus() const;
	void setGoalStatus(GoalStatuses value);
    virtual bool checkCondition(Enums::GameStatuses aGameStatus);
protected:
	int current;
	int needed;
	std::string description;
	GoalStatuses goalStatus;
};

