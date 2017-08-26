#include "HorizontalPanel.h"

HorizontalPanel::HorizontalPanel(
    std::shared_ptr<RenderingSystem>& aRenderingContext,
    std::shared_ptr<ILayout>& aLayout)
    : Composite(aRenderingContext, aLayout)
{
}

Size HorizontalPanel::getSize() const
{
    return panelSize;
}

void HorizontalPanel::setSize(Size size)
{
    panelSize = size;
}

void HorizontalPanel::addChild(const shared_ptr<IComposite>& child)
{
    child->setPosition(getNextHorizontalPosition());
    Composite::addChild(child);
}
