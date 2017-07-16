#pragma once

#include "IComposite.h"
#include <list>
#include "RenderingSystem.h"
#include "../../Input/InputHandler.h"

using std::list;

class Composite : public IComposite, public InputHandler, public std::enable_shared_from_this<Composite>
{
public:
    explicit Composite(std::shared_ptr<RenderingSystem>& aRenderingContext);
    Composite() = default;
    virtual ~Composite() = default;

    Position getNextHorizontalPosition() const;
    Position getNextVerticalPosition() const;

    void addChild(const shared_ptr<IComposite>& child) override;
    void removeChild(const shared_ptr<IComposite>& child) override;
    void draw() const override;
    weak_ptr<IComposite> getParent() const override;//правильно ли?
    Position getPosition() const override;
    void setPosition(Position pos) override;
    bool hasChildren() const;
    void setParent(weak_ptr<IComposite> aParent) override;
    bool hasParent() const override;

    // IComposite interface
    Position getLocalPosition() const override;
    void setLocalPosition(Position aPosition) override;
    void clearChildren() override;
    double getScalingFactor() const override;
    void setScalingFactor(double aScaleFactor) override;

    // InputHandler interface
    bool onClick(Position point) override;
    bool canDrag() const override;
    bool onDrag(Position aDirection) override;
    bool containsPoint(Position aPosition) const override;

protected:
    std::shared_ptr<RenderingSystem> renderer;
    list<shared_ptr<IComposite> > children;
    weak_ptr<IComposite> parent;
    Position localPosition{0, 0};
    double mScaleFactor = 0.0;
    Size mScaledSize{0, 0};
};

