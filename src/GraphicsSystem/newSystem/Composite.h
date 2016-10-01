#pragma once
#include "IComposite.h"
#include <list>
using std::list;


class Composite : public IComposite, public std::enable_shared_from_this<Composite>
{
public:

    Composite() = default;
    virtual ~Composite() = default;

    virtual void addChild(shared_ptr<IComposite> child) override;
    virtual void removeChild(shared_ptr<IComposite> child) override;
    virtual void draw() override;
    virtual weak_ptr<IComposite> getParent() const override;//правильно ли?
    virtual Position getPosition() const override;
    virtual void setPosition(Position pos) override;
    virtual bool hasChildren() const;
    virtual void setParent(weak_ptr<IComposite> aParent) override;
    virtual bool hasParent() const override;

protected:
    Position getNextPosition() const;

private:
    list<shared_ptr<IComposite> > children;
    weak_ptr<IComposite> parent;
    Position localPosition;
};

