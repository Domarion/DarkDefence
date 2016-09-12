#include "HorizontalPanel.h"

Size HorizontalPanel::getSize() const
{
    return panelSize;
}

void HorizontalPanel::setSize(Size size)
{
    panelSize = size;
}

void HorizontalPanel::addChild(shared_ptr<IComposite> child)
{

    child->setPosition(getNextPosition());
    Composite::addChild(child);

}
