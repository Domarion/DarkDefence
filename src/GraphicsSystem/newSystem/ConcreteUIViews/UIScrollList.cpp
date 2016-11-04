#include "UIScrollList.h"
#include <algorithm>
UIScrollList::UIScrollList(int aItemsToShow, std::shared_ptr<RenderingSystem> &aRenderingContext)
    :ConcreteComposite(aRenderingContext)
    , itemCountToShow(aItemsToShow)
    , toFirst(children.begin())
    , toLast(children.begin())
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

bool UIScrollList::onDrag(int direction)
{
    std::cout << "why cant drag?1111" << std::endl;

    if (direction == 0 || children.empty())
        return false;

    std::cout << "why cant drag?" << std::endl;
    size_t points = 1;//abs(direction);
    if (direction > 0)
        scrollUp(points);
    else
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

std::list<shared_ptr<IComposite> >::iterator &UIScrollList::getIteratorToFirst()
{
    return toFirst;
}

std::list<shared_ptr<IComposite> >::iterator &UIScrollList::getIteratorToLast()
{
    return toLast;
}

void UIScrollList::scrollUp(size_t amount)
{

    if (toFirst != children.begin())
    {
        size_t distance = std::distance(toFirst, children.begin());

        if (distance > amount)
            distance = amount;

        std::advance(toFirst, -distance);
        std::advance(toLast, -distance);
        recalcItemPositions();
    }
}

void UIScrollList::scrollDown(size_t amount)
{
    if (children.size() >= amount)
    {

        size_t distance = std::distance(toLast, children.end());
        if (distance > amount)
            distance = amount;

        std::advance(toFirst, distance);
        std::advance(toLast, distance);

        recalcItemPositions();
    }


}

void UIScrollList::recalcItemPositions()
{

    const int xPos{0};
    int yPos{0};

    for(auto firstIter = toFirst; firstIter != toLast; ++firstIter)
    {
        (*firstIter)->setPosition(Position(xPos, yPos));

        yPos += (*firstIter)->getSize().height;
    }
}

void UIScrollList::addChild(const shared_ptr<IComposite> &child)
{
    ConcreteComposite::addChild(child);
    if (children.size() == 1)
    {
        toFirst = children.begin();
        toLast = children.end();
    }
    else
        if (children.size() >= itemCountToShow)
        {
            std::advance(toLast, itemCountToShow - std::distance(toFirst, toLast));
        }
    recalcItemPositions();
}

void UIScrollList::removeChild(const shared_ptr<IComposite> &child)
{
    if (child != nullptr)
    {   

        auto childIterator = std::find(children.begin(), children.end(), child);

        if (childIterator == children.end())
            return;


        if (children.size() <= itemCountToShow)
        {
            children.erase(childIterator);
            toFirst = children.begin();
            toLast = children.end();
        }
        else
        if (childIterator == toFirst)
        {

            toFirst = children.erase(childIterator);
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
                toLast = toFirst;
                std::advance(toLast, firstLastDistance);

            }
            else
            {
                children.remove(child);
            }

            if (children.size() <= itemCountToShow)
            {
                toFirst = children.begin();
                toLast = children.end();
            }

        }


        recalcItemPositions();
    }
}

void UIScrollList::draw() const
{
    for(auto firstIter = toFirst; firstIter != toLast; ++firstIter)
        (*firstIter)->draw();
}

bool UIScrollList::onClick(SDL_Point *point)
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

            if (SDL_PointInRect(point, &childRect))
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
        removeChild(*clickedItemIter);

    return isSuccess;
}

bool UIScrollList::containsPoint(int x, int y) const
{
   Position pos = getPosition();
   Size size = getSize();

   if (x >= pos.x && x <= (pos.x + size.width) && y >= pos.y && y <= (pos.y + size.height))
       return true;
   return false;
}
