#define BOOST_TEST_MODULE TILEMAPMANAGERTESTS_TEST

#include <boost/test/unit_test.hpp>
#include "src/GlobalScripts/TileMapManager.h"

BOOST_AUTO_TEST_SUITE(TileMapManagerTestSuite)
struct TileMapManagerTestFixture
{
    vector<vector<int>> mapTemplate =
    {
        {-2, -2, -2, -2},
        {-2, -2, -2, -2},
        {-1, -1, -1, -1},
        {-2, -2, -2, -2},
        {-2, -2, -2, -2}
    };

    TileMapManager manager{mapTemplate};
};

BOOST_FIXTURE_TEST_CASE(ShouldFindLinePathAndBuildIt, TileMapManagerTestFixture)
{
    // Format (y, x) or (i, j) in other words
    std::pair<int, int> start{2, 3};
    std::pair<int, int> end{2, 0};

    list<pair<int, int>> expectedPath;
    const size_t pathSize = 4;
    const int i = 2;
    int j = 0;
    for(size_t counter = 0; counter < pathSize; ++counter)
    {
        expectedPath.emplace_back(std::make_pair(i, j++));
    }

    bool result = manager.waveAlgo(start, end);
    BOOST_CHECK_EQUAL(true, result);
    auto path = manager.getPath(end);

    auto expectedPathIterator = expectedPath.begin();
    auto expectedPathIteratorEnd = expectedPath.end();

    auto pathIterator = path->begin();
    auto pathIteratorEnd = path->end();

    BOOST_REQUIRE_EQUAL(expectedPath.size(), path->size());

    for(; expectedPathIterator != expectedPathIteratorEnd && pathIterator != pathIteratorEnd;
        ++expectedPathIterator, ++pathIterator)
    {
        BOOST_CHECK_EQUAL(expectedPathIterator->first, pathIterator->first);
        BOOST_CHECK_EQUAL(expectedPathIterator->second, pathIterator->second);
    }
}

BOOST_FIXTURE_TEST_CASE(ShouldConvertGlobalPosToLocal, TileMapManagerTestFixture)
{
    //assume that both of column and row sizes are equals to 48

    // Global Coords in format {x, y}
    auto mapIndex = manager.getPosFromGlobalCoords(Position{0 , 96});

    BOOST_CHECK_EQUAL(2, mapIndex.first);
    BOOST_CHECK_EQUAL(0, mapIndex.second);

    mapIndex = manager.getPosFromGlobalCoords(Position{0 , 0});

    BOOST_CHECK_EQUAL(0, mapIndex.first);
    BOOST_CHECK_EQUAL(0, mapIndex.second);

    mapIndex = manager.getPosFromGlobalCoords(Position{98 , 198});

    BOOST_CHECK_EQUAL(4, mapIndex.first);
    BOOST_CHECK_EQUAL(2, mapIndex.second);
}
BOOST_FIXTURE_TEST_CASE(ShouldLocalPosToGlobal, TileMapManagerTestFixture)
{
    auto globalPos = manager.getGlobalPosFromLocalCoords(std::make_pair(0 , 0));

    BOOST_CHECK_EQUAL(0, globalPos.x);
    BOOST_CHECK_EQUAL(0, globalPos.y);

    globalPos = manager.getGlobalPosFromLocalCoords(std::make_pair(1, 1));

    BOOST_CHECK_EQUAL(48, globalPos.x);
    BOOST_CHECK_EQUAL(48, globalPos.y);
}

BOOST_FIXTURE_TEST_CASE(ShouldFindRectPathAndBuildIt, TileMapManagerTestFixture)
{
    vector<vector<int>> mapTemplate =
    {
        {-2, -2, -2, -2, -2, -2, -2, -2},
        {-2, -2, -2, -2, -2, -2, -2, -2},
        {-2, -1, -1, -1, -1, -1, -2, -2},
        {-2, -1, -2, -2, -2, -1, -2, -2},
        {-2, -1, -2, -2, -2, -1, -2, -2},
        {-2, -1, -2, -2, -2, -1, -2, -2},
        {-2, -1, -1, -1, -1, -1, -2, -2},
        {-2, -2, -2, -2, -2, -2, -2, -2},
        {-2, -2, -2, -2, -2, -2, -2, -2},
        {-2, -2, -2, -2, -2, -2, -2, -2}
    };

    TileMapManager manager{mapTemplate};
    // Format (y, x) or (i, j) in other words
    std::pair<int, int> start{4, 1};
    std::pair<int, int> end{4, 5};

    list<pair<int, int>> expectedPath;
    int i = 4;
    int j = 5;
    expectedPath.emplace_back(std::make_pair(i--, j));
    expectedPath.emplace_back(std::make_pair(i--, j));

    const size_t linePathSize = 5;

    for(size_t counter = 0; counter < linePathSize; ++counter)
    {
        expectedPath.emplace_back(std::make_pair(i, j--));
    }

    expectedPath.emplace_back(std::make_pair(++i, ++j));
    expectedPath.emplace_back(std::make_pair(++i, j));


    bool result = manager.waveAlgo(start, end);
    BOOST_CHECK_EQUAL(true, result);
    auto path = manager.getPath(end);

    auto expectedPathIterator = expectedPath.begin();
    auto expectedPathIteratorEnd = expectedPath.end();

    auto pathIterator = path->begin();
    auto pathIteratorEnd = path->end();

    BOOST_REQUIRE_EQUAL(expectedPath.size(), path->size());

    for(; expectedPathIterator != expectedPathIteratorEnd && pathIterator != pathIteratorEnd;
        ++expectedPathIterator, ++pathIterator)
    {
        BOOST_CHECK_EQUAL(expectedPathIterator->first, pathIterator->first);
        BOOST_CHECK_EQUAL(expectedPathIterator->second, pathIterator->second);
    }
}

BOOST_FIXTURE_TEST_CASE(ShouldBuildRightPathTwice, TileMapManagerTestFixture)
{

    vector<vector<int>> mapTemplate =
    {
        {-2, -2, -2, -2, -2, -2, -2, -2},
        {-2, -2, -2, -2, -2, -2, -2, -2},
        {-2, -2, -2, -2, -2, -2, -2, -2},
        {-2, -2, -2, -1, -2, -2, -1, -2},
        {-2, -2, -2, -1, -2, -2, -1, -2},
        {-2, -1, -2, -1, -1, -1, -1, -2},
        {-2, -1, -2, -2, -1, -2, -2, -2},
        {-2, -1, -1, -1, -1, -2, -2, -2},
        {-2, -2, -2, -2, -2, -2, -2, -2},
        {-2, -2, -2, -2, -2, -2, -2, -2}
    };

    TileMapManager manager{mapTemplate};

    {
        // Format (y, x) or (i, j) in other words
        std::pair<int, int> start{3, 6};
        std::pair<int, int> end{3, 3};

        list<pair<int, int>> expectedPath1
            {
                {3, 3},
                {4, 3},
                {5, 3},
                {5, 4},
                {5, 5},
                {5, 6},
                {4, 6},
                {3, 6},
            };
        bool result = manager.waveAlgo(start, end);
        BOOST_CHECK_EQUAL(true, result);
        auto path = manager.getPath(end);

        auto expectedPathIterator = expectedPath1.begin();
        auto expectedPathIteratorEnd = expectedPath1.end();

        auto pathIterator = path->begin();
        auto pathIteratorEnd = path->end();

        BOOST_REQUIRE_EQUAL(expectedPath1.size(), path->size());

        for(; expectedPathIterator != expectedPathIteratorEnd && pathIterator != pathIteratorEnd;
            ++expectedPathIterator, ++pathIterator)
        {
            BOOST_CHECK_EQUAL(expectedPathIterator->first, pathIterator->first);
            BOOST_CHECK_EQUAL(expectedPathIterator->second, pathIterator->second);
        }
    }

    {

        std::pair<int, int> start{3, 3};
        std::pair<int, int> end{5, 1};

        list<pair<int, int>> expectedPath2
            {
                {5, 1},
                {6, 1},
                {7, 1},
                {7, 2},
                {7, 3},
                {7, 4},
                {6, 4},
                {5, 4},
                {5, 3},
                {4, 3},
                {3, 3},
            };
        bool result = manager.waveAlgo(start, end);
        BOOST_CHECK_EQUAL(true, result);
        auto path = manager.getPath(end);

        auto expectedPathIterator = expectedPath2.begin();
        auto expectedPathIteratorEnd = expectedPath2.end();

        auto pathIterator = path->begin();
        auto pathIteratorEnd = path->end();

        BOOST_REQUIRE_EQUAL(expectedPath2.size(), path->size());

        for(; expectedPathIterator != expectedPathIteratorEnd && pathIterator != pathIteratorEnd;
            ++expectedPathIterator, ++pathIterator)
        {
            BOOST_CHECK_EQUAL(expectedPathIterator->first, pathIterator->first);
            BOOST_CHECK_EQUAL(expectedPathIterator->second, pathIterator->second);
        }
    }
}


BOOST_AUTO_TEST_SUITE_END()
