#include <boost/optional.hpp>

#include "../include/MissionTumbler.hpp"
//TODO use normal path
#include "../../MissionSystem/Mission.h"

MissionTumbler::MissionTumbler(const MissionTumbler::TContainer& aMissions)
    : mMissions(aMissions)
    , mCurrentMissionIterator(mMissions.begin())
{
}

void MissionTumbler::SetMissions(MissionTumbler::TContainer&& aMissionContainer)
{
    mMissions = aMissionContainer;
    mCurrentMissionIterator = mMissions.begin();
}

bool MissionTumbler::HasMissions() const
{
    return !mMissions.empty();
}

boost::optional<Mission> MissionTumbler::getCurrentMission() const
{
    if (mMissions.empty())
    {
        return{};
    }

    if (mCurrentMissionIterator != mMissions.end())
    {
        return *mCurrentMissionIterator;
    }
    return {};
}

boost::optional<Mission> MissionTumbler::nextMission()
{
    if (mMissions.empty())
    {
        return{};
    }

    if (mCurrentMissionIterator == mMissions.end()
        || ++mCurrentMissionIterator == mMissions.end())
    {
        return {};
    }

    return *mCurrentMissionIterator;
}
