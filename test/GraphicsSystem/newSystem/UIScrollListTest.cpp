 
#define BOOST_TEST_MODULE UIScrollListTest
#include <boost/test/unit_test.hpp>
#include "src/GraphicsSystem/newSystem/ConcreteUIViews/UIScrollList.h"
BOOST_AUTO_TEST_SUITE(UIScrollListTestSuite)
struct UIScrollListFixture
{
std::shared_ptr<RenderingSystem> nullrendering = nullptr;
const int ItemsToShow = 3;
};



BOOST_FIXTURE_TEST_CASE(scrollShouldSaveItemCountToShow, UIScrollListFixture)
{
    auto scroll = std::make_shared<UIScrollList>(ItemsToShow, nullrendering);

    BOOST_CHECK_EQUAL(scroll->getItemCountToShow(), ItemsToShow);
}

BOOST_FIXTURE_TEST_CASE(scrollBorderPointersShouldMoveOnAdd, UIScrollListFixture)
{
    auto child = std::make_shared<ConcreteComposite>(nullrendering);
    auto scroll = std::make_shared<UIScrollList>(ItemsToShow, nullrendering);
    scroll->addChild(child);
    BOOST_CHECK(scroll->getIteratorToFirst() == scroll->getBeginIterator());
    BOOST_CHECK(scroll->getIteratorToLast() == scroll->getEndIterator());
}

BOOST_FIXTURE_TEST_CASE(scrollBorderLastPointerShouldMoveOnAddMoreThan, UIScrollListFixture)
{
    auto child1 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child2 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child3 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child4 = std::make_shared<ConcreteComposite>(nullrendering);

    auto scroll = std::make_shared<UIScrollList>(ItemsToShow, nullrendering);
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
    auto child1 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child2 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child3 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child4 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child5 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child6 = std::make_shared<ConcreteComposite>(nullrendering);

    auto scroll = std::make_shared<UIScrollList>(ItemsToShow, nullrendering);
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

    auto scroll = std::make_shared<UIScrollList>(ItemsToShow, nullrendering);

    BOOST_CHECK(std::distance(scroll->getIteratorToFirst(), scroll->getIteratorToLast()) == 0);
}

BOOST_FIXTURE_TEST_CASE(scrollShouldPointToOneAddedChild, UIScrollListFixture)
{

    auto scroll = std::make_shared<UIScrollList>(ItemsToShow, nullrendering);
    auto child1 = std::make_shared<ConcreteComposite>(nullrendering);
    scroll->addChild(child1);


    BOOST_CHECK(std::distance(scroll->getIteratorToFirst(), scroll->getIteratorToLast()) == 1);
}

BOOST_FIXTURE_TEST_CASE(scrollShouldBeEmptyAfterRemove, UIScrollListFixture)
{

    auto scroll = std::make_shared<UIScrollList>(ItemsToShow, nullrendering);
    auto child1 = std::make_shared<ConcreteComposite>(nullrendering);
    scroll->addChild(child1);

    scroll->removeChild(child1);

    BOOST_CHECK(scroll->getIteratorToFirst() == scroll->getBeginIterator());
    BOOST_CHECK(scroll->getIteratorToLast() == scroll->getEndIterator());
}


BOOST_FIXTURE_TEST_CASE(scrollPointersShouldMoveAfterRemove, UIScrollListFixture)
{

    auto child1 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child2 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child3 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child4 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child5 = std::make_shared<ConcreteComposite>(nullrendering);

    auto scroll = std::make_shared<UIScrollList>(ItemsToShow, nullrendering);
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

    auto child1 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child2 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child3 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child4 = std::make_shared<ConcreteComposite>(nullrendering);

    auto scroll = std::make_shared<UIScrollList>(ItemsToShow, nullrendering);
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

BOOST_FIXTURE_TEST_CASE(scrollPointersShouldMoveOnlyOnceAfterDown, UIScrollListFixture)
{

    auto child1 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child2 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child3 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child4 = std::make_shared<ConcreteComposite>(nullrendering);

    auto scroll = std::make_shared<UIScrollList>(ItemsToShow, nullrendering);
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

    auto child1 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child2 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child3 = std::make_shared<ConcreteComposite>(nullrendering);

    auto scroll = std::make_shared<UIScrollList>(ItemsToShow, nullrendering);
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);

    scroll->scrollDown(1);

    BOOST_CHECK(scroll->getIteratorToFirst() == scroll->getBeginIterator());
    BOOST_CHECK(scroll->getIteratorToLast() == scroll->getEndIterator());
}

BOOST_FIXTURE_TEST_CASE(scrollPointersShouldMoveOnlyToOne, UIScrollListFixture)
{

    auto child1 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child2 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child3 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child4 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child5 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child6 = std::make_shared<ConcreteComposite>(nullrendering);

    auto scroll = std::make_shared<UIScrollList>(ItemsToShow, nullrendering);
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

    auto child1 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child2 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child3 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child4 = std::make_shared<ConcreteComposite>(nullrendering);

    auto scroll = std::make_shared<UIScrollList>(ItemsToShow, nullrendering);
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

    auto child1 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child2 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child3 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child4 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child5 = std::make_shared<ConcreteComposite>(nullrendering);

    auto scroll = std::make_shared<UIScrollList>(ItemsToShow, nullrendering);
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

    auto child1 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child2 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child3 = std::make_shared<ConcreteComposite>(nullrendering);
    auto child4 = std::make_shared<ConcreteComposite>(nullrendering);

    auto scroll = std::make_shared<UIScrollList>(ItemsToShow, nullrendering);
    scroll->addChild(child1);
    scroll->addChild(child2);
    scroll->addChild(child3);
    scroll->addChild(child4);

    scroll->scrollDown(1);

    scroll->removeChild(child4);

    BOOST_CHECK(scroll->getIteratorToFirst() == scroll->getBeginIterator());
    BOOST_CHECK(scroll->getIteratorToLast() == scroll->getEndIterator());
}
BOOST_AUTO_TEST_SUITE_END()
