#pragma once

#include "../Composite.h"

class HorizontalPanel : public Composite
{
public:
    explicit HorizontalPanel(std::shared_ptr<RenderingSystem>& aRenderingContext, std::shared_ptr<ILayout>& aLayout);

    HorizontalPanel() = default;
    virtual ~HorizontalPanel() = default;

    // IComposite interface
    virtual Size getSize() const override;
    virtual void setSize(Size size) override;
    virtual void addChild(const shared_ptr<IComposite> &child) override;

private:
    Size panelSize;
};
