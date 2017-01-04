#pragma once
#include "../Composite.h"

class ConcreteComposite: public Composite
{
public:
    explicit ConcreteComposite(std::shared_ptr<RenderingSystem>& aRenderingContext);

    ConcreteComposite() = default;
    virtual ~ConcreteComposite() = default;

    // IComposite interface
public:
    virtual Size getSize() const override;
    virtual void setSize(Size size) override;
};
