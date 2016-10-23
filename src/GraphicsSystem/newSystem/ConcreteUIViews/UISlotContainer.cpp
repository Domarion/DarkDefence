#include "UISlotContainer.h"

UISlotContainer::UISlotContainer(std::string aEmptyImagePath,
                                 size_t aItemCount,
                                 Size aItemSize,
                                 std::shared_ptr<RenderingSystem> &aRenderer)
    :mItems(aItemCount)
    , mRenderer(aRenderer)
{
    for (auto& item : mItems)
    {
        item = std::make_shared<UISlot>(aEmptyImagePath, mRenderer);
        item->setSize(aItemSize);
    }
}

void UISlotContainer::LoadItemAtIndex(std::string &aPath, int aIndex)
{
    mItems[aIndex]->resetForeground();
    mItems[aIndex]->loadForeground(aPath);
}

void UISlotContainer::SetItemPos(Position aPos, int aIndex)
{
    mItems[aIndex]->setPosition(aPos);
}

void UISlotContainer::FillItemAtIndex(std::shared_ptr<UISlot> &aItem, int aIndex)
{
    mItems[aIndex] = aItem;
}

void UISlotContainer::CleanItemAtIndex(int aIndex)
{
    mItems[aIndex]->resetForeground();
}

void UISlotContainer::ConnectMethod(std::function<bool(int)> method)
{
    mConnectedMethod = method;
}

bool UISlotContainer::onClick(SDL_Point *point)
{
    if (mConnectedMethod != nullptr)
        for(size_t index = 0; index < mItems.size(); ++index)
        {
            SDL_Rect itemRect{
            mItems[index]->getPosition().x,
            mItems[index]->getPosition().y,
            mItems[index]->getSize().width,
            mItems[index]->getSize().height};

            if (SDL_PointInRect(point, &itemRect))
            {
                if (mConnectedMethod(index)) CleanItemAtIndex(index);
                return true;
            }
        }
    return false;
}

std::vector<std::shared_ptr<UISlot> > &UISlotContainer::getItems()
{
    return mItems;
}
