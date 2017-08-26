#pragma once

#include "IComposite.h"
#include <list>

struct ILayout
{
    using TIterator = std::list<std::shared_ptr<IComposite>>::iterator;
    virtual ~ILayout() = default;
    virtual void apply(std::list<std::shared_ptr<IComposite>>&) const = 0;
    virtual void apply(const TIterator& aFirst, const TIterator& aLast) const = 0;
};
