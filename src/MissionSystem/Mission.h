/*
 * Mission.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <boost/serialization/list.hpp>
#include <list>

#include "Reward.h"

#include <string>
#include "BasicGoal.h"
//#include <boost/serialization/export.hpp>
enum MissionStatuses
{
    mNOT_STARTED = 0,
	mIN_PROGRESS,
	mCOMPLETED,
	mFAILED
};

class Mission
{
    friend class boost::serialization::access;
    template <typename Archive>
      void serialize(Archive &ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_NVP(caption);
        ar & BOOST_SERIALIZATION_NVP(description);
        ar & BOOST_SERIALIZATION_NVP(goals);
        ar & BOOST_SERIALIZATION_NVP(reward);
        ar & boost::serialization::make_nvp("status", missionStatus);

    }
public:
	Mission();
	~Mission();
	std::string getCaption() const;
	void setCaption(std::string value);
	std::string getDescription() const;
	void setDescription(std::string value);
	MissionStatuses getStatus() const;

    MissionStatuses checkStatus();
	void setStatus(MissionStatuses value);
    void addGoal(BasicGoal* goal);
    void setReward(const Reward& someReward);
    std::list<std::string> getGoalsFullDesc();
    std::list<std::string> getGoalsNeeded();
    std::list<BasicGoal*>& getGoals();
    Reward& getReward();
private:
	std::string caption;
	std::string description;
    std::list<BasicGoal*> goals;
    Reward reward;
    MissionStatuses missionStatus;

};


