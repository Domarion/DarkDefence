#pragma once

#include "ILayout.h"

struct HorizontalLayout : public ILayout
{
    void apply(std::list<std::shared_ptr<IComposite> >&) const override;
    void apply(const TIterator& aFirst, const TIterator& aLast) const override;
};
