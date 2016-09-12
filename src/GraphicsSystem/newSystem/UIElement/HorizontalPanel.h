#pragma once
#include "../Composite.h"

class HorizontalPanel : public Composite
{
public:
    HorizontalPanel() = default;
    virtual ~HorizontalPanel() = default;
    // IComposite interface
    virtual Size getSize() const override;
    virtual void setSize(Size size) override;
    virtual void addChild(shared_ptr<IComposite> child) override;
private:
    Size panelSize;
};
