/*#define BOOST_TEST_MODULE RendererTest
#include <boost/test/unit_test.hpp>
//#include "src/GraphicsSystem/newSystem/RenderingSystem.h"

BOOST_AUTO_TEST_SUITE(RenderingTestSuite)

struct RenderingFixture
{
    typename FormatConvertor formatConvertor;
    typename RenderingSystem;
    typename Window;
    typename Size;
};



BOOST_FIXTURE_TEST_CASE(RendererScreenSizeAndWindowSizeShouldBeTheSame, RenderingFixture)
{
    const Size windowSize(800, 600);
    Window window(windowSize);
    RenderingSystem renderer(window);
    const Size windowSizeBad(100, 120);
    BOOST_CHECK_EQUAL(renderer.getScreenSize(), windowSizeBad);

}

BOOST_FIXTURE_TEST_CASE(RendererDPICheck, RenderingFixture)
{
    const Size windowSize(800, 600);
    Window window(windowSize);
    RenderingSystem renderer(window);
    const int unrealDPI = 0;
    BOOST_CHECK_EQUAL(renderer.getScreenDPI(), unrealDPI);

}

BOOST_FIXTURE_TEST_CASE(RendererMinimumDPIShouldBe160, RenderingFixture)
{
    const Size windowSize(800, 600);
    Window window(windowSize);
    RenderingSystem renderer(window);
    const int unrealDPI = 0;
    BOOST_CHECK_EQUAL(renderer.getMinimumDPI(), unrealDPI);

}

BOOST_FIXTURE_TEST_CASE(DPToPixelConversionCheck, RenderingFixture)
{
    const Size windowSize(800, 600);
    Window window(windowSize);
    RenderingSystem renderer(window);

    BOOST_CHECK_EQUAL(renderer.convertDensityPixelToRealPixel(10), 0);

}

BOOST_FIXTURE_TEST_CASE(PxToDensityPixelConversionCheck, RenderingFixture)
{
    const Size windowSize(800, 600);
    Window window(windowSize);
    RenderingSystem renderer(window);

    BOOST_CHECK_EQUAL(renderer.convertRealPixelToDensityPixel(10), 0);

}
BOOST_AUTO_TEST_SUITE_END()*/

