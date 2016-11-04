#define BOOST_TEST_MODULE TileTerrainMakerTest
#include <boost/test/unit_test.hpp>
#include "src/GraphicsSystem/newSystem/TileTerrainMaker.h"
BOOST_AUTO_TEST_SUITE(TileTerrainMakerTestSuite)

struct TileTerrainMakerFixture
{
     std::shared_ptr<RenderingSystem> nullRenderer = nullptr;
};


BOOST_FIXTURE_TEST_CASE(TilesShouldBeLoaded, TileTerrainMakerFixture)
{
   //Given
    const std::string legendString("50 50\n2\n@ grass\n| rocks");

    TileLegendCollection collection(nullRenderer);
   //When
    collection.parseString(legendString);

   //Then
     BOOST_CHECK_EQUAL(collection.size(), 2);

}


BOOST_AUTO_TEST_SUITE_END()
