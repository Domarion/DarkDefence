#pragma once
#include "IComposite.h"
#include <list>
using std::list;
#include "RenderingSystem.h"
#include "../../Input/InputHandler.h"

class Composite : public IComposite, public InputHandler, public std::enable_shared_from_this<Composite>
{
public:

    explicit Composite(std::shared_ptr<RenderingSystem>& aRenderingContext);
    Composite() = default;
    virtual ~Composite() = default;

    virtual void addChild(const shared_ptr<IComposite>& child) override;
    virtual void removeChild(const shared_ptr<IComposite>& child) override;
    virtual void draw() const override;
    virtual weak_ptr<IComposite> getParent() const override;//правильно ли?
    virtual Position getPosition() const override;
    virtual void setPosition(Position pos) override;
    virtual bool hasChildren() const;
    virtual void setParent(weak_ptr<IComposite> aParent) override;
    virtual bool hasParent() const override;
    // InputHandler interface
public:
    virtual bool onClick(Position point) override;


    Position getNextHorizontalPosition() const;
    Position getNextVerticalPosition() const;
protected:


    std::shared_ptr<RenderingSystem> renderer;

protected:
    list<shared_ptr<IComposite> > children;
    weak_ptr<IComposite> parent;
    Position localPosition{0, 0};
    double mScaleFactor = 0.0;
    Size mScaledSize;
    // IComposite interface
public:
    virtual Position getLocalPosition() const override;
    virtual void setLocalPosition(Position aPosition) override;


    // InputHandler interface
public:
    virtual bool canDrag() const override;
    virtual bool onDrag(int direction) override;

    // InputHandler interface
public:
    virtual bool containsPoint(int x, int y) const override;

    // IComposite interface
public:
    virtual void clearChildren() override;
    double getScalingFactor() const override;
    void setScalingFactor(double aScaleFactor) override;
};

