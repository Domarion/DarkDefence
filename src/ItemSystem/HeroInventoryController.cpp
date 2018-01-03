#include "HeroInventoryController.h"

HeroInventoryController::~HeroInventoryController()
{
    mView = nullptr;
}

void HeroInventoryController::setView(const std::shared_ptr<UISlotContainer>& aNewView)
{
    mView = aNewView;
}

const std::shared_ptr<UISlotContainer>& HeroInventoryController::getView() const
{
	return mView;
}

void HeroInventoryController::setModel(const std::shared_ptr<HeroInventory>& aNewModel)
{
    mModel = aNewModel;
}

const std::shared_ptr<HeroInventory>& HeroInventoryController::getModel() const
{
    return mModel;
}

void HeroInventoryController::initLocalPositions(Size aRectSize)
{
    if (mModel == nullptr)
        return;

    size_t count = mModel->getItemCount();
    mSlotsPositions.resize(count);
    Size itemSize(50, 50);
    int centerHorizontal{(aRectSize.width - itemSize.width)/2};
    int y = 0;


    for(size_t i = 0; i < count; ++i)
    {
       mSlotsPositions[i] = Position(centerHorizontal, y);
       y += itemSize.height;
    }
}

// TODO Remove hardcoded.
void HeroInventoryController::initView(std::shared_ptr<RenderingSystem>& aRenderer)
{
    if (mModel == nullptr)
        return;

    size_t count = mModel->getItemCount();

    if (count == 0)
        return;

    std::string emptySlotPath = "GameData/textures/EmptySlot.png";
    Size itemSize(50, 50);
    mView = std::make_shared<UISlotContainer>(emptySlotPath, count, itemSize, aRenderer);

    for(size_t i = 0; i < count; ++i)
    {
        std::string aItemPath = "GameData/textures/items/"
                + mModel->getItemFromIndex(i)->getCaption() + ".png";
        mView->LoadItemAtIndex(aItemPath, i);
        mView->SetItemPos(mSlotsPositions[i], i);

    }
    mView->ConnectMethod(std::bind( &HeroInventory::sendItem, mModel, std::placeholders::_1) );
    mModel->ConnectControllerReceiver(
        std::bind(
            &HeroInventoryController::receiveItemFromModel,
            this,
            std::placeholders::_1,
            std::placeholders::_2));
}


void HeroInventoryController::receiveItemFromModel(std::string aCaption, size_t aItemType)
{
    if (aCaption.empty())
        return;

    std::string imgPath = "GameData/textures/items/" + aCaption + ".png";
    mView->LoadItemAtIndex(imgPath, aItemType);
}
