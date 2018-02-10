#pragma once

#include <functional>
#include <vector>

#include "../UIElement/ConcreteComposite.h"
#include "UISlot.h"

class UISlotContainer final: public InputHandler
{
public:
    UISlotContainer(const std::string& aEmptyImagePath,
        size_t aItemCount,
        Size aItemSize,
        std::shared_ptr<RenderingSystem>& aRenderer);

    void LoadItemAtIndex(const std::string& aPath, size_t aIndex);
    void SetItemPos(Position aPos, size_t aIndex);
    void FillItemAtIndex(const std::shared_ptr<UISlot>& aItem, size_t aIndex);
    void CleanItemAtIndex(int aIndex);
    void ConnectMethod(std::function<bool(int)> aMethod);
    bool onClick(Position aPoint) override;
    const std::vector<std::shared_ptr<UISlot>>& getItems();
private:

    std::vector<std::shared_ptr<UISlot>> mItems;
    std::shared_ptr<RenderingSystem> mRenderer;

    std::function<bool(int)> mConnectedMethod;
};
