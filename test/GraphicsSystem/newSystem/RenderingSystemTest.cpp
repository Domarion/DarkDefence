#define BOOST_TEST_MODULE RendererTest
#include <boost/test/unit_test.hpp>
#include "src/GraphicsSystem/newSystem/RenderingSystem.h"

BOOST_AUTO_TEST_SUITE(RenderingTestSuite)

struct RenderingFixture
{

};



BOOST_FIXTURE_TEST_CASE(RendererScreenSizeAndWindowSizeShouldBeTheSame, RenderingFixture)
{
    Size windowSize(800, 600);
    RenderingSystem renderer(windowSize);
    BOOST_CHECK_EQUAL(renderer.getScreenSize(), windowSize);

}

BOOST_AUTO_TEST_SUITE_END()

