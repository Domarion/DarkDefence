#pragma once

#include <cereal/access.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/utility.hpp>
#include "Enums.h"

enum class GoalStatuses
{
    gIN_PROGRESS = 0,
	gCOMPLETED,
	gFAILED
};

class BasicGoal
{
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar(CEREAL_NVP(description), CEREAL_NVP(goalStatus), CEREAL_NVP(needed));
    }
public:

    BasicGoal() = default;
    BasicGoal(const std::string& aDescription, int aControlNumber);
    virtual ~BasicGoal() = default;

	int getCurrent() const;
    void setCurrent(int aCurrent);
	int getNeeded() const;
    void setNeeded(int aNeeded);
	std::string getDescription() const;
    void setDescription(const std::string& aDescription);
	GoalStatuses getGoalStatus() const;
    void setGoalStatus(GoalStatuses aGoalStatus);

    virtual bool checkCondition(Enums::GameStatuses aGameStatus);

protected:

	std::string description;
    int needed = 0;
    int current = 0;
    GoalStatuses goalStatus = GoalStatuses::gIN_PROGRESS;
};

