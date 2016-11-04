/*
 * BasicGoal.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once



#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/version.hpp>


#include <string>

enum class GoalStatuses
{
	gIN_PROGRESS,
	gCOMPLETED,
	gFAILED
};

class BasicGoal
{
    friend class boost::serialization::access;
    template <typename Archive>
      void serialize(Archive &ar, const unsigned int /*version*/)
    {
        ar & BOOST_SERIALIZATION_NVP(description);
        ar & BOOST_SERIALIZATION_NVP(goalStatus);
        ar & BOOST_SERIALIZATION_NVP(needed);

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
    virtual bool checkCondition();
protected:
	int current;
	int needed;
	std::string description;
	GoalStatuses goalStatus;
};

