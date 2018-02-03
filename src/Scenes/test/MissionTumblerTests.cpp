#define BOOST_TEST_MODULE MissionTumblerTests

#include <boost/test/included/unit_test.hpp>
#include "../include/MissionTumbler.hpp"
#include "../../MissionSystem/Mission.h"

BOOST_AUTO_TEST_SUITE(MissionTumblerTestSuite)

struct MissionTumblerFixture
{
    bool checkEqual(const Mission& aLeft, const Mission& aRight)
    {
        return aLeft.getCaption() == aRight.getCaption()
            && aLeft.getDescription() == aRight.getDescription();
    }

    const Mission TestMission1{"Mission1", "Description1", Reward{}};
    const Mission TestMission2{"Mission1", "Description1", Reward{}};

    const std::vector<Mission> TestMissions =
    {
        TestMission1,
        TestMission2,
    };

    MissionTumbler tumbler;

    MissionTumblerFixture()
        : tumbler(TestMissions)
    {
    }
};

BOOST_FIXTURE_TEST_CASE(ShouldReturnCurrentMission, MissionTumblerFixture)
{
    auto currentMission = tumbler.getCurrentMission();
    BOOST_REQUIRE(currentMission);

    BOOST_CHECK(checkEqual(TestMission1, *currentMission));
}

BOOST_FIXTURE_TEST_CASE(ShouldTurnToNextMission, MissionTumblerFixture)
{
    auto nextMission = tumbler.nextMission();
    BOOST_REQUIRE(nextMission);
    BOOST_CHECK(checkEqual(TestMission2, *nextMission));

    auto currentMission = tumbler.getCurrentMission();
    BOOST_REQUIRE(currentMission);
    BOOST_CHECK(checkEqual(TestMission2, *currentMission));
}

BOOST_AUTO_TEST_CASE(ShouldNotReturnMission)
{
    MissionTumbler tumbler({});
    BOOST_CHECK(!tumbler.nextMission());
    BOOST_CHECK(!tumbler.getCurrentMission());
}

BOOST_AUTO_TEST_SUITE_END()
