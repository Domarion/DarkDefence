#include "VerticalLayout.h"

void VerticalLayout::apply(std::list<std::shared_ptr<IComposite>>& aCollection) const
{
    apply(aCollection.begin(), aCollection.end());
}

void VerticalLayout::apply(const ILayout::TIterator& aFirst, const ILayout::TIterator& aLast) const
{
    int y = 0;
    for (auto item = aFirst; item != aLast; ++item)
    {
        if (*item)
        {
            auto& itemValue = *item;
            Position pos{itemValue->getLocalPosition().x, y};
            itemValue->setLocalPosition(pos);
            y += itemValue->getSize().height;
        }
    }
}
