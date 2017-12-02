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

enum class MissionStatuses
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
        ar(
            CEREAL_NVP(caption),
            CEREAL_NVP(description),
            CEREAL_NVP(goals),
            CEREAL_NVP(reward),
            CEREAL_NVP(missionStatus));
    }

public:

    Mission() = default;
    Mission(const std::string& aCaption, const std::string& aDescription, const Reward& aReward);
    ~Mission() = default;

    const std::string& getCaption() const;
    void setCaption(const std::string& aCaption);
    const std::string& getDescription() const;
    void setDescription(const std::string& aDescription);
	MissionStatuses getStatus() const;

    MissionStatuses checkStatus(Enums::GameStatuses aGameStatus);
	void setStatus(MissionStatuses value);
    void addGoal(const std::shared_ptr<BasicGoal>& aGoal);
    void setReward(const Reward& aReward);
    std::list<std::string> getGoalsFullDesc() const;
    std::list<std::string> getGoalsNeeded() const;
    const std::list<std::shared_ptr<BasicGoal>>& getGoals() const;
    const Reward& getReward() const;

    void reset();

private:

	std::string caption;
	std::string description;
    std::list<std::shared_ptr<BasicGoal>> goals;
    Reward reward;
    MissionStatuses missionStatus = MissionStatuses::mNOT_STARTED;
};


