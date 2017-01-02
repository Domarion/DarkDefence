#define BOOST_TEST_MODULE COMPOSITE_TEST

#include <boost/test/unit_test.hpp>
#include "src/GraphicsSystem/newSystem/Composite.h"
#include "src/GraphicsSystem/newSystem/Leaf.h"

BOOST_AUTO_TEST_SUITE(CompositeTestSuite)

struct CompositeFixture
{
    class compositeT: public Composite
    {
    public:


        // IComposite interface
    public:
        virtual Size getSize() const override
        {
            return mScaledSize;
        }
        virtual void setSize(Size aSize) override
        {
            mScaledSize = aSize;
        }
    };

    class leafT: public Leaf
    {


        // IComposite interface
    public:
        virtual void draw() const override
        {

        }
        virtual Size getSize() const override
        {
            return mScaledSize;
        }
        virtual void setSize(Size aSize) override
        {
            mScaledSize = aSize;
        }
    };
};



BOOST_FIXTURE_TEST_CASE(ShouldHaveChildren, CompositeFixture)
{

    auto composite = std::make_shared<compositeT>();
    composite->addChild(std::move(std::make_shared<leafT>()));
    BOOST_CHECK_EQUAL(composite->hasChildren(), true);
}

BOOST_FIXTURE_TEST_CASE(ShouldHaveNoChildren, CompositeFixture)
{

    auto composite = std::make_shared<compositeT>();
    BOOST_CHECK_EQUAL(composite->hasChildren(), false);
}

BOOST_FIXTURE_TEST_CASE(ShouldHaveNoChildrenAfterRemoveLast, CompositeFixture)
{

    auto composite = std::make_shared<compositeT>();
    std::shared_ptr<leafT> child = std::make_shared<leafT>();
    composite->addChild(child);
    composite->removeChild(child);
    BOOST_CHECK_EQUAL(composite->hasChildren(), false);
}

BOOST_FIXTURE_TEST_CASE(ShouldHaveChildrenAfterRemoveOneOf, CompositeFixture)
{

    auto composite = std::make_shared<compositeT>();
    auto child1 = std::make_shared<leafT>();
    auto child2 = std::make_shared<leafT>();
    composite->addChild(child1);
    composite->addChild(child2);
    composite->removeChild(child1);
    BOOST_CHECK_EQUAL(composite->hasChildren(), true);
}

BOOST_FIXTURE_TEST_CASE(ShouldHaveChildrenAfterRemoveNonAdded, CompositeFixture)
{

    auto composite = std::make_shared<compositeT>();
    std::shared_ptr<leafT> child1 = std::make_shared<leafT>();
    std::shared_ptr<leafT> child2 = std::make_shared<leafT>();
    composite->addChild(child1);
    composite->removeChild(child2);
    BOOST_CHECK_EQUAL(composite->hasChildren(), true);
}


BOOST_FIXTURE_TEST_CASE(ShouldHaveNoParent, CompositeFixture)
{

    auto composite = std::make_shared<compositeT>();
    BOOST_CHECK_EQUAL(composite->hasParent(), false);
}

BOOST_FIXTURE_TEST_CASE(ShouldHaveParentAfterAdd, CompositeFixture)
{

    auto compositeParent = std::make_shared<compositeT>();
    auto compositeChild = std::make_shared<compositeT>();
    compositeParent->addChild(compositeChild);
    BOOST_CHECK_EQUAL(compositeChild->hasParent(), true);
}

BOOST_FIXTURE_TEST_CASE(ParentAndChildsParentShouldBeEqual, CompositeFixture)
{

    auto compositeParent = std::make_shared<compositeT>();
    auto compositeChild = std::make_shared<compositeT>();
    compositeParent->addChild(compositeChild);
    auto childsParent = compositeChild->getParent().lock();
    BOOST_CHECK_EQUAL(childsParent, compositeParent);
}

BOOST_FIXTURE_TEST_CASE(LeafShouldThrowAfterAddChildAttempt, CompositeFixture)
{
    auto leaf = std::make_shared<leafT>();
    auto leafChild = std::make_shared<leafT>();

    BOOST_CHECK_THROW(leaf->addChild(leafChild), std::logic_error);
}

BOOST_FIXTURE_TEST_CASE(LeafShouldThrowAfterRemoveChildAttempt, CompositeFixture)
{
    auto leaf = std::make_shared<leafT>();
    auto leafChild = std::make_shared<leafT>();

    BOOST_CHECK_THROW(leaf->removeChild(leafChild), std::logic_error);
}

BOOST_FIXTURE_TEST_CASE(ChildsDefaultPosShouldBeEqualParentPos, CompositeFixture)
{
    auto composite = std::make_shared<compositeT>();
    auto leafChild = std::make_shared<leafT>();

    composite->setPosition(std::move(Position(0, 20)));
    composite->addChild(leafChild);
    const Position childPos(0, 20);
    BOOST_CHECK_EQUAL(leafChild->getPosition(), childPos);
}

BOOST_FIXTURE_TEST_CASE(ChildsPosShouldBeCalculatedWithParentPos, CompositeFixture)
{
    auto composite = std::make_shared<compositeT>();
    auto leafChild = std::make_shared<leafT>();

    composite->setPosition(std::move(Position(0, 20)));
    composite->addChild(leafChild);
    leafChild->setPosition(std::move(Position(10, 20)));
    const Position childPos(10, 40);
    BOOST_CHECK_EQUAL(leafChild->getPosition(), childPos);
}

BOOST_FIXTURE_TEST_CASE(ThrowWhenSettingChildPosAxisLTZero, CompositeFixture)
{
    auto composite = std::make_shared<compositeT>();
    auto leafChild = std::make_shared<leafT>();

    composite->setPosition(std::move(Position(0, 20)));
    composite->addChild(leafChild);


    BOOST_CHECK_THROW(leafChild->setPosition(std::move(Position(-100, 20))), std::logic_error);
}

BOOST_FIXTURE_TEST_CASE(NoThrowSettingLeafPosAxisLTZero, CompositeFixture)
{
    auto leafChild = std::make_shared<leafT>();

    BOOST_CHECK_NO_THROW(leafChild->setPosition(std::move(Position(-100, 20))));
}

BOOST_FIXTURE_TEST_CASE(LeafPosAxisShouldLTZero, CompositeFixture)
{
    auto leafChild = std::make_shared<leafT>();
    const Position pos(-100, 20);
    leafChild->setPosition(pos);
    BOOST_CHECK_EQUAL(leafChild->getPosition(), pos);
}

BOOST_FIXTURE_TEST_CASE(CompositeChildrenShouldBeScaledAndMoved, CompositeFixture)
{
    const Size expectedCompositeSize{2000, 4000};
    const Size expectedChildSize{400, 600};
    const Size expectedChildLeaf1Size{200, 100};
    const Size expectedChildLeaf2Size{300,  200};

    const Position expectedChildCompositePos{100, 300};
    const Position expectedChildLeaf1Position{150, 330};
    const Position expectedChildLeaf2Position{350, 300};

    auto composite = std::make_shared<compositeT>();
    composite->setSize(Size(1000, 2000));
    composite->setScalingFactor(2);

    const Position pos(100, 300);

    auto childComposite = std::make_shared<compositeT>();
    childComposite->setLocalPosition(pos);
    childComposite->setScalingFactor(2);
    childComposite->setSize(Size(200, 300));

    auto childLeaf1 = std::make_shared<leafT>();
    childLeaf1->setLocalPosition(Position(50, 30));
    childLeaf1->setSize(Size(100, 50));

    childComposite->addChild(childLeaf1);

    auto childLeaf2 = std::make_shared<leafT>();
    childLeaf2->setLocalPosition(childComposite->getNextHorizontalPosition());
    childLeaf2->setSize(Size(150, 100));

    childComposite->addChild(childLeaf2);

    composite->addChild(childComposite);

    BOOST_CHECK_EQUAL(composite->getSize(), expectedCompositeSize);
    BOOST_CHECK_EQUAL(childComposite->getSize(), expectedChildSize);
    BOOST_CHECK_EQUAL(childLeaf1->getSize(), expectedChildLeaf1Size);
    BOOST_CHECK_EQUAL(childLeaf2->getSize(), expectedChildLeaf2Size);

    BOOST_CHECK_EQUAL(childComposite->getPosition(), expectedChildCompositePos);
    BOOST_CHECK_EQUAL(childLeaf1->getPosition(), expectedChildLeaf1Position);
    BOOST_CHECK_EQUAL(childLeaf2->getPosition(), expectedChildLeaf2Position);

}
BOOST_AUTO_TEST_SUITE_END()
