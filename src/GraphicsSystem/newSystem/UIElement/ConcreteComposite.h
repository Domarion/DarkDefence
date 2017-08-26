#pragma once

#include "../Composite.h"

class ConcreteComposite: public Composite
{
public:
    explicit ConcreteComposite(
        std::shared_ptr<RenderingSystem>& aRenderingContext, const std::shared_ptr<ILayout>& aLayout);

    ConcreteComposite() = default;
    virtual ~ConcreteComposite() = default;

    void setLayout(const std::shared_ptr<ILayout>& aLayout);

    // IComposite interface
    Size getSize() const override;
    void setSize(Size size) override;
};
