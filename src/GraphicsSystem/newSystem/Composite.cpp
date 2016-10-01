#include "Composite.h"

void Composite::addChild(shared_ptr<IComposite> child)
{
    if (child != nullptr)
    {
        child->setParent(shared_from_this());
        children.push_back(child);
    }
}

void Composite::removeChild(shared_ptr<IComposite> child)
{
    if (child != nullptr)
        children.remove(child);
}

void Composite::draw()
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

Position Composite::getNextPosition() const
{
    Position localPos{0, 0};
    if (hasChildren())
    {
        shared_ptr<IComposite> lastChild = children.back();
        localPos.x = lastChild->getPosition().x + lastChild->getSize().width;
        localPos.y = lastChild->getPosition().y;
    }
    return localPos;
}

bool Composite::hasParent() const
{
    return !getParent().expired();
}

void Composite::setParent(weak_ptr<IComposite> aParent)
{
    parent = aParent;
}
