﻿ 
#define BOOST_TEST_MODULE UIScrollListTest
#include <boost/test/unit_test.hpp>
#include "src/GraphicsSystem/newSystem/ConcreteUIViews/UIScrollList.h"
#include "src/GraphicsSystem/newSystem/VerticalLayout.h"
#include "src/GraphicsSystem/newSystem/StubLayout.h"

BOOST_AUTO_TEST_SUITE(UIScrollListTestSuite)

struct UIScrollListFixture
{
    std::shared_ptr<RenderingSystem> nullrendering = nullptr;
    std::shared_ptr<ILayout> verticalLayout = std::make_shared<VerticalLayout>();
    std::shared_ptr<ILayout> emptyLayout = std::make_shared<StubLayout>();

    const int ItemsToShow = 3;

    auto makeScroll()
    {
        return std::make_shared<UIScrollList>(ItemsToShow, nullrendering, verticalLayout);
    }

    auto makeConcreteComposite()
    {
        return std::make_shared<ConcreteComposite>(nullrendering, emptyLayout);
    }
};


BOOST_FIXTURE_TEST_CASE(scrollShouldSaveItemCountToShow, UIScrollListFixture)
{
    auto scroll = makeScroll();

    BOOST_CHECK_EQUAL(scroll->getItemCountToShow(), ItemsToShow);
}

BOOST_FIXTURE_TEST_CASE(scrollBorderPointersShouldMoveOnAdd, UIScrollListFixture)
{
    auto child = makeConcreteComposite();
    auto scroll = makeScroll();
    scroll->addChild(child);
    BOOST_CHECK(scroll->getIteratorToFirst() == scroll->getBeginIterator());
    BOOST_CHECK(scroll->getIteratorToLast() == scroll->getEndIterator());
}

BOOST_FIXTURE_TEST_CASE(scrollBorderLastPointerShouldMoveOnAddMoreThan, UIScrollListFixture)
{
    auto child1 = makeConcreteComposite();
    auto child2 = makeConcreteComposite();
    auto child3 = makeConcreteComposite();
    auto child4 = makeConcreteComposite();

    auto scroll = makeScroll();
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);
    scroll->addChild(child4);

    auto last_iterator = scroll->getBeginIterator();
    std::advance(last_iterator, 3);
    BOOST_CHECK(scroll->getIteratorToFirst() == scroll->getBeginIterator());
    BOOST_CHECK(scroll->getIteratorToLast() == last_iterator);
}

BOOST_FIXTURE_TEST_CASE(scrollPointersDistanceShouldBeLEConst, UIScrollListFixture)
{
    auto child1 = makeConcreteComposite();
    auto child2 = makeConcreteComposite();
    auto child3 = makeConcreteComposite();
    auto child4 = makeConcreteComposite();
    auto child5 = makeConcreteComposite();
    auto child6 = makeConcreteComposite();

    auto scroll = makeScroll();
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);
    scroll->addChild(child4);
    scroll->addChild(child5);
    scroll->addChild(child6);

    BOOST_CHECK(std::distance(scroll->getIteratorToFirst(), scroll->getIteratorToLast()) == ItemsToShow);
}

BOOST_FIXTURE_TEST_CASE(scrollShouldBeEmptyIfNoInsertions, UIScrollListFixture)
{

    auto scroll = makeScroll();

    BOOST_CHECK(std::distance(scroll->getIteratorToFirst(), scroll->getIteratorToLast()) == 0);
}

BOOST_FIXTURE_TEST_CASE(scrollShouldPointToOneAddedChild, UIScrollListFixture)
{

    auto scroll = makeScroll();
    auto child1 = makeConcreteComposite();
    scroll->addChild(child1);


    BOOST_CHECK(std::distance(scroll->getIteratorToFirst(), scroll->getIteratorToLast()) == 1);
}

BOOST_FIXTURE_TEST_CASE(scrollShouldBeEmptyAfterRemove, UIScrollListFixture)
{

    auto scroll = makeScroll();
    auto child1 = makeConcreteComposite();
    scroll->addChild(child1);

    scroll->removeChild(child1);

    BOOST_CHECK(scroll->getIteratorToFirst() == scroll->getBeginIterator());
    BOOST_CHECK(scroll->getIteratorToLast() == scroll->getEndIterator());
}


BOOST_FIXTURE_TEST_CASE(scrollPointersShouldMoveAfterRemove, UIScrollListFixture)
{

    auto child1 = makeConcreteComposite();
    auto child2 = makeConcreteComposite();
    auto child3 = makeConcreteComposite();
    auto child4 = makeConcreteComposite();
    auto child5 = makeConcreteComposite();

    auto scroll = makeScroll();
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);
    scroll->addChild(child4);
    scroll->addChild(child5);

    scroll->removeChild(child1);
    scroll->removeChild(child5);
}

BOOST_FIXTURE_TEST_CASE(scrollPointersShouldMoveAfterDown, UIScrollListFixture)
{

    auto child1 = makeConcreteComposite();
    auto child2 = makeConcreteComposite();
    auto child3 = makeConcreteComposite();
    auto child4 = makeConcreteComposite();

    auto scroll = makeScroll();
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);
    scroll->addChild(child4);

    auto second_iterator = scroll->getBeginIterator();
    std::advance(second_iterator, 1);

    scroll->scrollDown(1);


    BOOST_CHECK(scroll->getIteratorToFirst() == second_iterator);
    BOOST_CHECK(scroll->getIteratorToLast() == scroll->getEndIterator());
}

BOOST_FIXTURE_TEST_CASE(scrollPointersShouldMoveAfterDownAndLastNEEnd, UIScrollListFixture)
{

    auto child1 = makeConcreteComposite();
    auto child2 = makeConcreteComposite();
    auto child3 = makeConcreteComposite();
    auto child4 = makeConcreteComposite();
    auto child5 = makeConcreteComposite();

    auto scroll = makeScroll();
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);
    scroll->addChild(child4);
    scroll->addChild(child5);

    auto second_iterator = scroll->getBeginIterator();
    std::advance(second_iterator, 1);

    scroll->scrollDown(1);

    auto second_last_iterator = scroll->getBeginIterator();
    std::advance(second_last_iterator, 4);


    BOOST_CHECK(scroll->getIteratorToFirst() == second_iterator);
    BOOST_CHECK(scroll->getIteratorToLast() == second_last_iterator);
}

BOOST_FIXTURE_TEST_CASE(scrollPointersShouldMoveOnlyOnceAfterDown, UIScrollListFixture)
{

    auto child1 = makeConcreteComposite();
    auto child2 = makeConcreteComposite();
    auto child3 = makeConcreteComposite();
    auto child4 = makeConcreteComposite();

    auto scroll = makeScroll();
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);
    scroll->addChild(child4);

    auto second_iterator = scroll->getBeginIterator();
    std::advance(second_iterator, 1);

    scroll->scrollDown(2);


    BOOST_CHECK(scroll->getIteratorToFirst() == second_iterator);
    BOOST_CHECK(scroll->getIteratorToLast() == scroll->getEndIterator());
}

BOOST_FIXTURE_TEST_CASE(scrollPointersShouldntMoveAfterDown, UIScrollListFixture)
{

    auto child1 = makeConcreteComposite();
    auto child2 = makeConcreteComposite();
    auto child3 = makeConcreteComposite();

    auto scroll = makeScroll();
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);

    scroll->scrollDown(1);

    BOOST_CHECK(scroll->getIteratorToFirst() == scroll->getBeginIterator());
    BOOST_CHECK(scroll->getIteratorToLast() == scroll->getEndIterator());
}

BOOST_FIXTURE_TEST_CASE(scrollPointersShouldMoveOnlyToOne, UIScrollListFixture)
{

    auto child1 = makeConcreteComposite();
    auto child2 = makeConcreteComposite();
    auto child3 = makeConcreteComposite();
    auto child4 = makeConcreteComposite();
    auto child5 = makeConcreteComposite();
    auto child6 = makeConcreteComposite();

    auto scroll = makeScroll();
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);
    scroll->addChild(child4);
    scroll->addChild(child5);
    scroll->addChild(child6);

    auto second_iterator = scroll->getBeginIterator();
    std::advance(second_iterator, 1);

    auto last_iterator = scroll->getBeginIterator();
    std::advance(last_iterator, 4);
    scroll->scrollDown(1);

    BOOST_CHECK(scroll->getIteratorToFirst() == second_iterator);
    BOOST_CHECK(scroll->getIteratorToLast() == last_iterator);
}

BOOST_FIXTURE_TEST_CASE(scrollPointersShouldMoveUp, UIScrollListFixture)
{

    auto child1 = makeConcreteComposite();
    auto child2 = makeConcreteComposite();
    auto child3 = makeConcreteComposite();
    auto child4 = makeConcreteComposite();

    auto scroll = makeScroll();
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);
    scroll->addChild(child4);

    scroll->scrollDown(1);

    auto last_iterator = scroll->getBeginIterator();
    std::advance(last_iterator, 3);

    scroll->scrollUp(1);


    BOOST_CHECK(scroll->getIteratorToFirst() == scroll->getBeginIterator());
    BOOST_CHECK(scroll->getIteratorToLast() == last_iterator);
}


BOOST_FIXTURE_TEST_CASE(removeAfterScrollShouldMovePointers, UIScrollListFixture)
{

    auto child1 = makeConcreteComposite();
    auto child2 = makeConcreteComposite();
    auto child3 = makeConcreteComposite();
    auto child4 = makeConcreteComposite();
    auto child5 = makeConcreteComposite();

    auto scroll = makeScroll();
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);
    scroll->addChild(child4);
    scroll->addChild(child5);



    scroll->scrollDown(1);

    scroll->removeChild(child4);

    auto first_iterator = scroll->getBeginIterator();
    std::advance(first_iterator, 1);


    BOOST_CHECK(scroll->getIteratorToFirst() == first_iterator);
    BOOST_CHECK(scroll->getIteratorToLast() == scroll->getEndIterator());
}

BOOST_FIXTURE_TEST_CASE(removeAfterScrollShouldntMoveLast, UIScrollListFixture)
{

    auto child1 = makeConcreteComposite();
    auto child2 = makeConcreteComposite();
    auto child3 = makeConcreteComposite();
    auto child4 = makeConcreteComposite();

    auto scroll = makeScroll();
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);
    scroll->addChild(child4);

    scroll->scrollDown(1);

    scroll->removeChild(child4);

    BOOST_CHECK(scroll->getIteratorToFirst() == scroll->getBeginIterator());
    BOOST_CHECK(scroll->getIteratorToLast() == scroll->getEndIterator());
}

BOOST_FIXTURE_TEST_CASE(removeAtEndShouldMoveUpper, UIScrollListFixture)
{

    auto child1 = makeConcreteComposite();
    auto child2 = makeConcreteComposite();
    auto child3 = makeConcreteComposite();
    auto child4 = makeConcreteComposite();

    auto scroll = makeScroll();
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);
    scroll->addChild(child4);

    scroll->scrollDown(1);

    scroll->removeChild(child4);

    BOOST_CHECK(scroll->getIteratorToFirst() == scroll->getBeginIterator());
    BOOST_CHECK(scroll->getIteratorToLast() == scroll->getEndIterator());
}


BOOST_FIXTURE_TEST_CASE(ScrollUpAfterScrollDown, UIScrollListFixture)
{

    auto child1 = makeConcreteComposite();
    auto child2 = makeConcreteComposite();
    auto child3 = makeConcreteComposite();
    auto child4 = makeConcreteComposite();

    auto scroll = makeScroll();
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);
    scroll->addChild(child4);

    scroll->scrollDown(1);

    scroll->scrollUp(2);

    auto last_iterator = scroll->getBeginIterator();
    std::advance(last_iterator, 3);

    BOOST_CHECK(scroll->getIteratorToFirst() == scroll->getBeginIterator());
    BOOST_CHECK(scroll->getIteratorToLast() == last_iterator);
}

BOOST_FIXTURE_TEST_CASE(ItemPositionsShouldBeTheSameAfterScroll, UIScrollListFixture)
{
    auto child1 = makeConcreteComposite();
    auto child2 = makeConcreteComposite();
    auto child3 = makeConcreteComposite();
    auto child4 = makeConcreteComposite();
    auto child5 = makeConcreteComposite();

    auto scroll = makeScroll();
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);
    scroll->addChild(child4);
    scroll->addChild(child5);

    std::vector<Position> childPositions
    {
        child1->getPosition(),
        child2->getPosition(),
        child3->getPosition(),
    };

    std::vector<Size> childSizes
    {
        child1->getSize(),
        child2->getSize(),
        child3->getSize(),
    };
    scroll->scrollDown(3);

    auto checkbegin = scroll->getBeginIterator();
    std::advance(checkbegin, 2);
    BOOST_CHECK(scroll->getIteratorToFirst() == checkbegin);
    BOOST_CHECK(scroll->getIteratorToLast() == scroll->getEndIterator());

    scroll->scrollUp(3);

    std::vector<Position> childPositionsNew
    {
        child1->getPosition(),
        child2->getPosition(),
        child3->getPosition(),
    };

    std::vector<Size> childSizesNew
    {
        child1->getSize(),
        child2->getSize(),
        child3->getSize(),
    };

    BOOST_CHECK(std::equal(childPositions.cbegin(), childPositions.cend(), childPositionsNew.cbegin(), childPositionsNew.cend()));
    BOOST_CHECK(std::equal(childSizes.cbegin(), childSizes.cend(), childSizesNew.cbegin(), childSizesNew.cend()));

    auto last_iterator = scroll->getBeginIterator();
    std::advance(last_iterator, 3);

    BOOST_CHECK(scroll->getIteratorToFirst() == scroll->getBeginIterator());
    BOOST_CHECK(scroll->getIteratorToLast() == last_iterator);
}
BOOST_AUTO_TEST_SUITE_END()
