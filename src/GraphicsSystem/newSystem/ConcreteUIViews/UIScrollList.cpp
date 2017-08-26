#include "UIScrollList.h"
#include <algorithm>

UIScrollList::UIScrollList(
    int aItemsToShow, std::shared_ptr<RenderingSystem>& aRenderingContext, const std::shared_ptr<ILayout>& aLayout)
    : ConcreteComposite(aRenderingContext, aLayout)
    , itemCountToShow(aItemsToShow)
    , toFirst(children.begin())
    , toLast(children.end())
{
}

void UIScrollList::ConnectMethod(std::function<bool (int)> method)
{
    connectedMethod = method;
}

bool UIScrollList::canDrag() const
{
    return children.size() > itemCountToShow;
}

bool UIScrollList::onDrag(Position aDirection)
{
    if (aDirection.y == 0 || children.empty())
        return false;

    size_t points = abs(aDirection.y)/3 + 1;

    if (aDirection.y > 0)
    {
        scrollUp(points);
        return true;
    }

    scrollDown(points);

    return true;
}

int UIScrollList::getItemCountToShow()
{
    return itemCountToShow;
}

int UIScrollList::getChildrenCount() const
{
    return children.size();
}

std::list<shared_ptr<IComposite> >::const_iterator UIScrollList::getBeginIterator() const
{
    return children.begin();
}

std::list<shared_ptr<IComposite> >::const_iterator UIScrollList::getEndIterator() const
{
    return children.end();
}

std::list<shared_ptr<IComposite> >::iterator& UIScrollList::getIteratorToFirst()
{
    return toFirst;
}

std::list<shared_ptr<IComposite> >::iterator& UIScrollList::getIteratorToLast()
{
    return toLast;
}

void UIScrollList::scrollUp(size_t amount)//TODO::Crash
{
    if (toFirst != children.begin())
    {
        size_t distance = std::distance(children.begin(), toFirst);
        size_t lastDistance = std::distance(toFirst, toLast);
        toFirst = children.begin();
        if (distance > amount)
        {
            std::advance(toFirst, distance - amount);
        }
        toLast = toFirst;

        std::advance(toLast, lastDistance);
        recalcItemPositions();
    }
}

void UIScrollList::scrollDown(size_t amount)
{
    if (toLast == children.end())
        return;

    size_t distance = std::distance(toLast, children.end());

    if (distance > amount)
        distance = amount;

    if (distance > 0)
    {
        std::advance(toFirst, distance);
        std::advance(toLast, distance);

        recalcItemPositions();
    }
}

void UIScrollList::recalcItemPositions()
{
    if (mLayout)
    {
        mLayout->apply(toFirst, toLast);
    }
}

void UIScrollList::addChild(const shared_ptr<IComposite>& child)
{
    ConcreteComposite::addChild(child);

    if (children.size() == 1)
    {
        toFirst = children.begin();
        toLast = children.end();
    }
    else if (children.size() >= itemCountToShow)
    {
        std::advance(toLast, itemCountToShow - std::distance(toFirst, toLast));
    }

    recalcItemPositions();
}

void UIScrollList::removeChild(const shared_ptr<IComposite>& child)//TODO::Wrong Logic
{
    if (child != nullptr)
    {
        auto childIterator = std::find(children.begin(), children.end(), child);

        if (childIterator == children.end())
            return;

        if (children.size() <= itemCountToShow + 1)
        {
            children.erase(childIterator);
            toFirst = children.begin();
            toLast = children.end();
        }
        else if (childIterator == toFirst)
        {

            toFirst = children.erase(childIterator);

            toLast = toFirst;

            if (std::distance(toFirst, children.end()) >= itemCountToShow)
                std::advance(toLast, itemCountToShow);
            if (children.size() <= itemCountToShow)
                toLast = children.end();

        }
        else
        {

            int childIterDistance = std::distance(toFirst, childIterator);
            int firstLastDistance = std::distance(toFirst, toLast);
            if (childIterDistance > 0 && childIterDistance < firstLastDistance)
            {
                childIterator = children.erase(childIterator);
                int beginDistance = std::distance(toFirst, children.end());
                if (beginDistance >= itemCountToShow)
                {
                    toLast = toFirst;
                    std::advance(toLast, itemCountToShow);
                }
                else
                    toLast = children.end();

            }
        }

        int fistLastDistance = std::distance(toFirst, toLast);
        if (fistLastDistance < itemCountToShow)
        {
            int beginFirstDistance = std::distance(children.begin(), toFirst);
            if (beginFirstDistance > 0)
            {
                toFirst = children.begin();
                std::advance(toFirst, beginFirstDistance - 1);
            }
        }

        recalcItemPositions();
    }
}

void UIScrollList::draw() const
{
    for(auto firstIter = toFirst; firstIter != toLast; ++firstIter)
    {
        (*firstIter)->draw();
    }
}

bool UIScrollList::onClick(Position point)
{
    auto clickedItemIter = toLast;
    bool isSuccess = false;

    for(auto childIter = toFirst; childIter != toLast; ++childIter)
    {
        InputHandler* inputHandler = dynamic_cast<InputHandler*>(childIter->get());
        if (inputHandler != nullptr && inputHandler->onClick(point))
        {
            clickedItemIter = childIter;
            isSuccess = true;
            break;
        }
        else
        {
            Size size = childIter->get()->getSize();
            Position position = childIter->get()->getLocalPosition();
            SDL_Rect childRect{position.x, position.y, size.width, size.height};

            SDL_Point sPoint{point.x, point.y};

            if (SDL_PointInRect(&sPoint, &childRect))
            {
                clickedItemIter = childIter;
                isSuccess = true;
                break;
            }
        }
    }

    if (clickedItemIter != toLast
        && connectedMethod != nullptr
        && connectedMethod(std::distance(children.begin(), clickedItemIter)))
    {
        removeChild(*clickedItemIter);
    }

    return isSuccess;
}

bool UIScrollList::containsPoint(Position aPosition) const
{
    Position pos = getPosition();
    Size size = getSize();

    return aPosition.x >= pos.x
        && aPosition.x <= (pos.x + size.width)
        && aPosition.y >= pos.y
        && aPosition.y <= (pos.y + size.height);
}
