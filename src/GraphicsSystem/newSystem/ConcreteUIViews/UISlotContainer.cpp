#include "UISlotContainer.h"
#include "../StubLayout.h"

UISlotContainer::UISlotContainer(
    const std::string& aEmptyImagePath,
    size_t aItemCount,
    Size aItemSize,
    std::shared_ptr<RenderingSystem>& aRenderer)
    : ConcreteComposite(aRenderer, std::make_shared<StubLayout>())
    , mItems(aItemCount)
    , mConnectedMethod(nullptr)
{
    for (auto& item : mItems)
    {
        item = std::make_shared<UISlot>(aEmptyImagePath, aRenderer);
        item->setSize(aItemSize);
    }
}

void UISlotContainer::LoadItemAtIndex(const std::string& aPath, size_t aIndex)
{
    mItems[aIndex]->resetForeground();
    mItems[aIndex]->loadForeground(aPath);
    mItems[aIndex]->setParent(shared_from_this());
}

void UISlotContainer::SetItemPos(Position aPos, size_t aIndex)
{
    mItems[aIndex]->setPosition(aPos);
}

void UISlotContainer::FillItemAtIndex(const std::shared_ptr<UISlot>& aItem, size_t aIndex)
{
    mItems[aIndex] = aItem;
    mItems[aIndex]->setParent(shared_from_this());
}

void UISlotContainer::CleanItemAtIndex(int aIndex)
{
    mItems[aIndex]->resetForeground();
}

void UISlotContainer::ConnectMethod(std::function<bool(int)> aMethod)
{
    mConnectedMethod = aMethod;
}

bool UISlotContainer::onClick(Position aPoint)
{
    if (!mConnectedMethod)
    {
        return false;
    }

    SDL_Point sPoint{aPoint.x, aPoint.y};

    for(size_t index = 0; index < mItems.size(); ++index)
    {
        SDL_Rect itemRect
        {
            mItems[index]->getPosition().x,
            mItems[index]->getPosition().y,
            mItems[index]->getSize().width,
            mItems[index]->getSize().height};

        if (SDL_PointInRect(&sPoint, &itemRect))
        {
            if (mConnectedMethod(index))
            {
                CleanItemAtIndex(index);
            }
            return true;
        }
    }

    return false;
}

const std::vector<std::shared_ptr<UISlot>>& UISlotContainer::getItems()
{
    return mItems;
}

void UISlotContainer::draw() const
{
    for(const auto& child : mItems)
    {
        child->draw();
    }
}

