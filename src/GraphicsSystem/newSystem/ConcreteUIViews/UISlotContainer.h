#pragma once

#include "../UIElement/ConcreteComposite.h"
#include "UISlot.h"
#include <functional>
#include <vector>

class UISlotContainer final: public InputHandler
{
public:
    UISlotContainer(const std::string& aEmptyImagePath,
        size_t aItemCount,
        Size aItemSize,
        std::shared_ptr<RenderingSystem>& aRenderer);
    virtual ~UISlotContainer() = default;

    void LoadItemAtIndex(const std::string& aPath, size_t aIndex);
    void SetItemPos(Position aPos, size_t aIndex);
    void FillItemAtIndex(const std::shared_ptr<UISlot>& aItem, size_t aIndex);
    void CleanItemAtIndex(int aIndex);
    void ConnectMethod(std::function<bool(int)> aMethod);
    virtual bool onClick(Position aPoint) override;
    const std::vector<std::shared_ptr<UISlot>>& getItems();
private:

    std::vector<std::shared_ptr<UISlot>> mItems;
    std::shared_ptr<RenderingSystem> mRenderer;
    std::function<bool(int)> mConnectedMethod;


};
