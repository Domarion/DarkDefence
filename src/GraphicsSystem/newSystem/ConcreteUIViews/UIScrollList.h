#pragma once
#include <functional>
#include "../UIElement/ConcreteComposite.h"

class UIScrollList final: public ConcreteComposite
{
public:
    explicit UIScrollList(int aItemsToShow
                          , std::shared_ptr<RenderingSystem>& aRenderingContext);
    virtual ~UIScrollList() = default;

    virtual void ConnectMethod(std::function<bool(int)> method);
    virtual bool canDrag() const override;
    virtual bool onDrag(int direction) override;
    int getItemCountToShow();

    std::list<shared_ptr<IComposite> >::const_iterator getBeginIterator() const;
    std::list<shared_ptr<IComposite> >::const_iterator getEndIterator() const;

    std::list<shared_ptr<IComposite> >::iterator& getIteratorToFirst();
    std::list<shared_ptr<IComposite> >::iterator& getIteratorToLast();
    void scrollUp(size_t amount);
    void scrollDown(size_t amount);

private:
    int itemCountToShow;
    std::list<shared_ptr<IComposite> >::iterator toFirst, toLast;

    std::function<bool(int)> connectedMethod;
    void recalcItemPositions();

    // IComposite interface
public:
    virtual void addChild(const shared_ptr<IComposite>& child) override;
    virtual void removeChild(const shared_ptr<IComposite> &child) override;
    virtual void draw() const override;

    // InputHandler interface
public:
    virtual bool onClick(SDL_Point *point) override;
};
