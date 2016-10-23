#pragma once

#include "../UIElement/ConcreteComposite.h"
#include "UISlot.h"
#include <functional>
#include <vector>

class UISlotContainer final: public InputHandler
{
public:
    UISlotContainer(std::string aEmptyImagePath,
        size_t aItemCount,
        Size aItemSize,
        std::shared_ptr<RenderingSystem>& aRenderer);
    virtual ~UISlotContainer() = default;

    void LoadItemAtIndex(std::string& aPath, int aIndex);
    void SetItemPos(Position aPos, int aIndex);
    void FillItemAtIndex(std::shared_ptr<UISlot>& aItem, int aIndex);
    void CleanItemAtIndex(int aIndex);
    void ConnectMethod(std::function<bool(int)> method);
    virtual bool onClick(SDL_Point* point) override;
    std::vector<std::shared_ptr<UISlot> >& getItems();
private:

    std::vector<std::shared_ptr<UISlot> > mItems;
    std::shared_ptr<RenderingSystem> mRenderer;
    std::function<bool(int)> mConnectedMethod;


};
//TODO:: продумать интерфейс и реализацию
