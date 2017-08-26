#include "Composite.h"

Composite::Composite(std::shared_ptr<RenderingSystem>& aRenderingContext, const std::shared_ptr<ILayout>& aLayout)
    : IComposite()
    , renderer(aRenderingContext)
    , mLayout(aLayout)
{
}

void Composite::addChild(const shared_ptr<IComposite>& child)
{
    if (child != nullptr)
    {
        std::weak_ptr<Composite> weak_this = shared_from_this();
        if (weak_this.expired())
        {
            throw std::runtime_error("shared_ptr expired, why?");
        }
        else
        {
            child->setParent(weak_this);
            // Потомок может полностью перекрывать родителя. В этом случае масштабирование не нужно.
            if (child->getSize() != getSize())
                child->setScalingFactor(this->getScalingFactor());
            children.push_back(child);
        }

        if (mLayout)
        {
            mLayout->apply(children);
        }
    }
}

void Composite::removeChild(const shared_ptr<IComposite>& child)
{
    if (child != nullptr)
        children.remove(child);
}

void Composite::draw() const
{
    for(const auto& child : children)
        child->draw();
}

weak_ptr<IComposite> Composite::getParent() const
{
    return parent;
}

Position Composite::getPosition() const
{
    Position globalPosition = localPosition;
    if (hasParent())
    {
        shared_ptr<IComposite>  parentPtr = getParent().lock();
        Position parentPosition = parentPtr->getPosition();
        globalPosition.x += parentPosition.x;
        globalPosition.y += parentPosition.y;
    }
    return globalPosition;
}

void Composite::setPosition(Position pos)
{
    if (hasParent() && (pos.x < 0 || pos.y < 0))
        throw std::logic_error("Error: relative to parent coord cannot be less than 0");
    localPosition = pos;
}

bool Composite::hasChildren() const
{
    return !children.empty();
}

Position Composite::getNextHorizontalPosition() const
{
    Position localPos{0, 0};
    if (hasChildren())
    {
        shared_ptr<IComposite> lastChild = children.back();
        localPos.x = lastChild->getLocalPosition().x + lastChild->getSize().width;
    }
    return localPos;
}

Position Composite::getNextVerticalPosition() const
{
    Position localPos{0, 0};
    if (hasChildren())
    {
        shared_ptr<IComposite> lastChild = children.back();
        localPos.y = lastChild->getLocalPosition().y + lastChild->getSize().height;
    }
    return localPos;
}

Position Composite::getLocalPosition() const
{

    return localPosition;
}

void Composite::setLocalPosition(Position aPosition)
{
    localPosition = aPosition;
}

bool Composite::canDrag() const
{
    for (auto& child: children)
    {
        if (child.get() != nullptr)
        {
            InputHandler* handler= dynamic_cast<InputHandler*>(child.get());
            if (handler != nullptr)
            {
                if (handler->canDrag())
                    return true;
            }
        }
    }
    return false;
}

bool Composite::onDrag(Position aDirection)
{
    for (auto& child: children)
    {
        if (child)
        {
            auto handler = std::dynamic_pointer_cast<InputHandler>(child);
            if (handler && handler->onDrag(aDirection))
            {
                return true;
            }
        }
    }

    return false;
}

bool Composite::containsPoint(Position aPosition) const
{
    for (const auto& child: children)
    {
        if (child)
        {
            auto handler= std::dynamic_pointer_cast<InputHandler>(child);
            if (handler && handler->containsPoint(aPosition))
            {
                return true;
            }
        }
    }

    return false;
}

void Composite::clearChildren()
{
    children.clear();
}

bool Composite::hasParent() const
{
    return !getParent().expired();
}

void Composite::setParent(weak_ptr<IComposite> aParent)
{
    parent = aParent;
}

bool Composite::onClick(Position point)
{
    for(const auto& child : children)
    {
        InputHandler* handler = dynamic_cast<InputHandler*>(child.get());
        if (handler != nullptr && handler->onClick(point))
            return true;
    }
    return false;
}

double Composite::getScalingFactor() const
{
    return mScaleFactor;
}

void Composite::setScalingFactor(double aScaleFactor)
{
    const double EPSe3 = 1e-3;
    if (fabs(mScaleFactor - aScaleFactor) < EPSe3)
        return;

    mScaleFactor = aScaleFactor;
    mScaledSize = getSize();
    mScaledSize *= mScaleFactor;
    setSize(mScaledSize);

    for(auto& child : children)
    {
        child->setScalingFactor(mScaleFactor);
    }
}
