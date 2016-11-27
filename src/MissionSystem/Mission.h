/*
 * Mission.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "BasicGoal.h"
#include "Reward.h"
#include <cereal/types/memory.hpp>

enum MissionStatuses
{
    mNOT_STARTED = 0,
	mIN_PROGRESS,
	mCOMPLETED,
	mFAILED
};

class Mission
{
    friend class cereal::access;
    template <typename Archive>
     void serialize(Archive &ar)
    {
        ar(caption, description, goals, reward, cereal::make_nvp("status", missionStatus));
    }
public:
	Mission();
    Mission(std::string aCaption, std::string aDescription, const Reward& aReward);
	~Mission();
	std::string getCaption() const;
	void setCaption(std::string value);
	std::string getDescription() const;
	void setDescription(std::string value);
	MissionStatuses getStatus() const;

    MissionStatuses checkStatus(Enums::GameStatuses aGameStatus);
	void setStatus(MissionStatuses value);
    void addGoal(std::shared_ptr<BasicGoal> goal);
    void setReward(const Reward& someReward);
    std::list<std::string> getGoalsFullDesc();
    std::list<std::string> getGoalsNeeded();
    std::list<std::shared_ptr<BasicGoal>>& getGoals();
    Reward& getReward();
    void reset();
private:
	std::string caption;
	std::string description;
    std::list<std::shared_ptr<BasicGoal>> goals;
    Reward reward;
    MissionStatuses missionStatus;

};


