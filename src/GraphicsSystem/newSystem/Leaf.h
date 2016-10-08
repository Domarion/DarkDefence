#pragma oncer
#include "IComposite.h"
#include "RenderingSystem.h"

class Leaf : public IComposite
{
public:
    explicit Leaf(std::shared_ptr<RenderingSystem>& aRenderingContext);

    Leaf() = default;
    virtual ~Leaf() = default;

    virtual void addChild(shared_ptr<IComposite> child) override;
    virtual void removeChild(shared_ptr<IComposite> child) override;
    virtual weak_ptr<IComposite> getParent() const override;

    // IComposite interface
    virtual Position getPosition() const override;
    virtual void setPosition(Position pos) override;

private:
    mutable std::shared_ptr<RenderingSystem> renderer;

    weak_ptr<IComposite> parent;
    Position localPosition;



    // IComposite interface
public:
    virtual void setParent(weak_ptr<IComposite> aParent) override;
    bool hasParent() const override;
};
