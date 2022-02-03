#include "../include/MissionTumbler.hpp"
#include <boost/optional.hpp>
#include <algorithm>

//TODO use normal path

MissionTumbler::MissionTumbler(const MissionTumbler::TContainer& aMissions)
    : mMissions(aMissions)
    , mCurrentMissionIterator(mMissions.begin())
{
}

void MissionTumbler::setMissions(MissionTumbler::TContainer&& aMissionContainer)
{
    mMissions = aMissionContainer;
    mCurrentMissionIterator = mMissions.begin();
}

bool MissionTumbler::hasMissions() const
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

bool MissionTumbler::setCurrentMissionByName(const std::string& aMissionCaption)
{
    auto comparer = [&aMissionCaption](const auto& aMission) -> bool
    {
        return aMission.getCaption() == aMissionCaption;
    };

    auto missionIter = std::find_if(mMissions.begin(), mMissions.end(), comparer);

    if (missionIter == mMissions.end())
    {
        return false;
    }

    mCurrentMissionIterator = missionIter;
    return true;
}

void MissionTumbler::resetCurrentMission()
{
    mCurrentMissionIterator = mMissions.end();
}
