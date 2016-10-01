#include "Leaf.h"
#include <exception>
void Leaf::addChild(shared_ptr<IComposite> child)
{

    throw std::logic_error("Error: add child to leaf");
}

void Leaf::removeChild(shared_ptr<IComposite> child)
{
    throw std::logic_error("Error: remove child from leaf");

}

weak_ptr<IComposite> Leaf::getParent() const
{
    return parent;
}

Position Leaf::getPosition() const
{
    Position globalPosition = localPosition;
    if (!getParent().expired())
    {
        shared_ptr<IComposite>  parentPtr = getParent().lock();
        Position parentPosition = parentPtr->getPosition();
        globalPosition.x += parentPosition.x;
        globalPosition.y += parentPosition.y;
    }
    return globalPosition;
}

void Leaf::setPosition(Position pos)
{
    localPosition = pos;
}

void Leaf::setParent(weak_ptr<IComposite> aParent)
{
    parent = aParent;
}
