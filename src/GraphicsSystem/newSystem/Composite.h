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

    virtual void addChild(shared_ptr<IComposite> child) override;
    virtual void removeChild(shared_ptr<IComposite> child) override;
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

protected:
    Position getNextPosition() const;
    std::shared_ptr<RenderingSystem> renderer;

protected:
    list<shared_ptr<IComposite> > children;
    weak_ptr<IComposite> parent;
    Position localPosition;
};

