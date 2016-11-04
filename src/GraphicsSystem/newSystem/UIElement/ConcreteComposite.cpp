#include "ConcreteComposite.h"

ConcreteComposite::ConcreteComposite(std::shared_ptr<RenderingSystem> &aRenderingContext)
    :Composite(aRenderingContext)
{

}

Size ConcreteComposite::getSize() const
{
    return mSize;
}

void ConcreteComposite::setSize(Size size)
{
    mSize = size;
}

