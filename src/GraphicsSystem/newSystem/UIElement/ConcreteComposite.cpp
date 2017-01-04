#include "ConcreteComposite.h"

ConcreteComposite::ConcreteComposite(std::shared_ptr<RenderingSystem> &aRenderingContext)
    :Composite(aRenderingContext)
{

}

Size ConcreteComposite::getSize() const
{
    return mScaledSize;
}

void ConcreteComposite::setSize(Size size)
{
    mScaledSize = size;
}

