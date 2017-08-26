#pragma once

#include "ILayout.h"

struct VerticalLayout : public ILayout
{
    void apply(std::list<std::shared_ptr<IComposite>>& aCollection) const override;
    void apply(const TIterator& aFirst, const TIterator& aLast) const override;
};
