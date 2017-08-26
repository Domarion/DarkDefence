#include "ConcreteComposite.h"

ConcreteComposite::ConcreteComposite(
    std::shared_ptr<RenderingSystem>& aRenderingContext, const std::shared_ptr<ILayout>& aLayout)
    : Composite(aRenderingContext, aLayout)
{
}

void ConcreteComposite::setLayout(const std::shared_ptr<ILayout>& aLayout)
{
    mLayout = aLayout;
}

Size ConcreteComposite::getSize() const
{
    return mScaledSize;
}

void ConcreteComposite::setSize(Size size)
{
    mScaledSize = size;
}

