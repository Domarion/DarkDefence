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

}

bool UIScrollList::onDrag(int direction)
{

}

int UIScrollList::getItemCountToShow()
{
    return itemCountToShow;
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
}

void UIScrollList::removeChild(const shared_ptr<IComposite> &child)
{
    if (child != nullptr)
    {   

        auto childIterator = std::find(children.begin(), children.end(), child);

        if (childIterator == children.end())
            return;


        if (childIterator == toFirst)
        {

            toFirst = children.erase(childIterator);

        }
        else
            if (childIterator == toLast)
            {
                toLast = children.erase(toLast);

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




//        if (children.size() <= itemCountToShow)
//        {
//            toFirst = children.begin();
//            toLast = children.end();

//        }
//        else
//        {

//           size_t distance = std::distance(toFirst, children.end());

//           if (distance > itemCountToShow)
//               distance = itemCountToShow;
//           toLast = toFirst;
//           std::advance(toLast, distance);
//        }
    }
}

void UIScrollList::draw() const
{

}
