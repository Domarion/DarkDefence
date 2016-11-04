#include "HorizontalPanel.h"

HorizontalPanel::HorizontalPanel(std::shared_ptr<RenderingSystem> &aRenderingContext)
    :Composite(aRenderingContext)
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

void HorizontalPanel::addChild(const shared_ptr<IComposite> &child)
{

    child->setPosition(getNextPosition());
    Composite::addChild(child);

}
