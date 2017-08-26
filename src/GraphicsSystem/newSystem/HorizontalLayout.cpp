#include "HorizontalLayout.h"

void HorizontalLayout::apply(std::list<std::shared_ptr<IComposite>>& aCollection) const
{
    apply(aCollection.begin(), aCollection.end());
}

void HorizontalLayout::apply(const ILayout::TIterator& aFirst, const ILayout::TIterator& aLast) const
{
    int x = 0;
    for (auto item = aFirst; item != aLast; ++item)
    {
        if (*item)
        {
            auto& itemValue = *item;
            Position pos{x, itemValue->getLocalPosition().y};
            itemValue->setLocalPosition(pos);
            x += itemValue->getSize().width;
        }
    }
}
