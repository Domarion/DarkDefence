#pragma oncer
#include "IComposite.h"


class Leaf : public IComposite
{
public:

    Leaf() = default;
    virtual ~Leaf() = default;

    virtual void addChild(shared_ptr<IComposite> child) override;
    virtual void removeChild(shared_ptr<IComposite> child) override;
    virtual weak_ptr<IComposite> getParent() const override;

    // IComposite interface
    virtual Position getPosition() const override;
    virtual void setPosition(Position pos) override;

private:
    weak_ptr<IComposite> parent;
    Position localPosition;



    // IComposite interface
public:
    virtual void setParent(weak_ptr<IComposite> aParent) override;
};
