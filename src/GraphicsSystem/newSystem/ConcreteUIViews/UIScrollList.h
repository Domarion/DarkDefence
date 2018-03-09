#pragma once

#include <functional>

#include "../UIElement/ConcreteComposite.h"

class UIScrollList final: public ConcreteComposite
{
public:
    explicit UIScrollList(
        int aItemsToShow, std::shared_ptr<RenderingSystem>& aRenderingContext, const std::shared_ptr<ILayout>& aLayout);
    virtual ~UIScrollList() = default;

    virtual void ConnectMethod(std::function<bool(int)> method);
    int getItemCountToShow();
    int getChildrenCount() const;
    std::list<shared_ptr<IComposite> >::const_iterator getBeginIterator() const;
    std::list<shared_ptr<IComposite> >::const_iterator getEndIterator() const;

    std::list<shared_ptr<IComposite> >::iterator& getIteratorToFirst();
    std::list<shared_ptr<IComposite> >::iterator& getIteratorToLast();
    void scrollUp(size_t amount);
    void scrollDown(size_t amount);

    // IComposite interface
    void addChild(const shared_ptr<IComposite>& child) override;
    void removeChild(const shared_ptr<IComposite>& child) override;
    void draw() const override;

    // InputHandler interface
    virtual bool canDrag() const override;
    virtual bool onDrag(Position aDirection) override;
    bool onClick(Position point) override;
    bool containsPoint(Position aPosition) const override;

private:
    size_t itemCountToShow;
    std::list<shared_ptr<IComposite> >::iterator toFirst, toLast;

    std::function<bool(int)> connectedMethod;
    void recalcItemPositions();
};
