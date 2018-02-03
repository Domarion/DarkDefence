#pragma once

#include <vector>
#include <boost/optional/optional_fwd.hpp>

class Mission;

class MissionTumbler
{
public:
    using TContainer = std::vector<Mission>;

    explicit MissionTumbler(const TContainer& aMissions);
    MissionTumbler() = default;

    void SetMissions(TContainer&& aMissionContainer);

    bool HasMissions() const;

    boost::optional<Mission> getCurrentMission() const;
    boost::optional<Mission> nextMission();

private:
    TContainer mMissions;
    TContainer::iterator mCurrentMissionIterator = mMissions.begin();
};
