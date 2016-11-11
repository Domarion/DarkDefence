#include "Composite.h"

Composite::Composite(std::shared_ptr<RenderingSystem> &aRenderingContext)
    :IComposite()
    , renderer(aRenderingContext)
{

}

void Composite::addChild(const shared_ptr<IComposite> &child)
{
    if (child != nullptr)
    {
        child->setParent(shared_from_this());
        children.push_back(child);
    }
}

void Composite::removeChild(const shared_ptr<IComposite> &child)
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

Position Composite::getNextPosition() const
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

bool Composite::onDrag(int direction)
{
    std::cout << "TryTo?" << std::endl;

    for (auto& child: children)
    {
        if (child.get() != nullptr)
        {
            InputHandler* handler= dynamic_cast<InputHandler*>(child.get());
            if (handler != nullptr)
            {
                std::cout << "NotNull" << std::endl;
                if (handler->onDrag(direction))
                    return true;
            }
        }
    }
    return false;
}

bool Composite::containsPoint(int x, int y) const
{
    for (auto& child: children)
    {
        if (child.get() != nullptr)
        {
            InputHandler* handler= dynamic_cast<InputHandler*>(child.get());
            if (handler != nullptr)
            {
                if (handler->containsPoint(x, y))
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
    for(const auto &child : children)
    {
        InputHandler* handler = dynamic_cast<InputHandler*>(child.get());
        if (handler != nullptr && handler->onClick(point))
               return true;
    }
    return false;
}
