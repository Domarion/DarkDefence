#pragma once

#include "../Composite.h"

class ConcreteComposite: public Composite
{
public:
    explicit ConcreteComposite(std::shared_ptr<RenderingSystem>& aRenderingContext);

    ConcreteComposite() = default;
    virtual ~ConcreteComposite() = default;

    // IComposite interface
    Size getSize() const override;
    void setSize(Size size) override;
};
