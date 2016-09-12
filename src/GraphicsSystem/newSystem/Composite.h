#pragma once
#include "IComposite.h"
#include <list>
using std::list;


class Composite : public IComposite
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
protected:
    Position getNextPosition() const;
private:
    list<shared_ptr<IComposite> > children;
    weak_ptr<IComposite> parent;
    Position localPosition;


};

