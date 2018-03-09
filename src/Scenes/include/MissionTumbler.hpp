#pragma once

#include <vector>

#include <boost/optional/optional_fwd.hpp>

#include "../../MissionSystem/Mission.h"

class MissionTumbler
{
public:
    using TContainer = std::vector<Mission>;

    explicit MissionTumbler(const TContainer& aMissions);
    MissionTumbler() = default;

    void setMissions(TContainer&& aMissionContainer);

    bool hasMissions() const;

    boost::optional<Mission> getCurrentMission() const;
    boost::optional<Mission> nextMission();

    bool setCurrentMissionByName(const std::string& aMissionCaption);

    void resetCurrentMission();

private:
    TContainer mMissions;
    TContainer::iterator mCurrentMissionIterator = mMissions.begin();
};
