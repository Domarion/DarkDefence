#pragma once

#include "IComposite.h"
#include "RenderingSystem.h"

class Leaf : public IComposite
{
public:
    explicit Leaf(std::shared_ptr<RenderingSystem>& aRenderingContext);

    Leaf() = default;
    virtual ~Leaf() = default;

    virtual void addChild(const shared_ptr<IComposite>& child) override;
    virtual void removeChild(const shared_ptr<IComposite>& child) override;
    virtual weak_ptr<IComposite> getParent() const override;

    // IComposite interface
    virtual Position getPosition() const override;
    virtual void setPosition(Position pos) override;

    virtual void setParent(weak_ptr<IComposite> aParent) override;
    bool hasParent() const override;

    virtual Position getLocalPosition() const override;
    void setLocalPosition(Position aPosition) override;

    void setScalingFactor(double aScaleFactor) override;
    double getScalingFactor() const override;

private:
    mutable std::shared_ptr<RenderingSystem> renderer;

    weak_ptr<IComposite> parent;
    Position localPosition{0,0};
    double mScaleFactor = 0.0;

protected:
    Size mScaledSize{0,0};
};
