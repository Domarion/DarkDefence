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
    virtual bool onClick(SDL_Point *point) override;


    Position getNextPosition() const;
    Position getNextVerticalPosition() const;
protected:


    std::shared_ptr<RenderingSystem> renderer;

protected:
    list<shared_ptr<IComposite> > children;
    weak_ptr<IComposite> parent;
    Position localPosition;

    // IComposite interface
public:
    virtual Position getLocalPosition() const override;

    // InputHandler interface
public:
    virtual bool canDrag() const override;
    virtual bool onDrag(int direction) override;

    // InputHandler interface
public:
    virtual bool containsPoint(int x, int y) const override;
};

