#include <sstream>

#include <cereal/archives/json.hpp>

#include "HeroInventoryController.h"
#include "../Utility/textfilefunctions.h"

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

// deprecated
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
void HeroInventoryController::initView(
    std::shared_ptr<RenderingSystem>& aRenderer,
    const std::string& aConfPath)
{
    if (mModel == nullptr)
        return;

    size_t count = mModel->getItemCount();

    if (count == 0)
        return;

    string textString;
    androidText::loadTextFileToString(aConfPath, textString);

    std::istringstream stream(textString);
    cereal::JSONInputArchive jsonArchive(stream);

    SlotConfig config;
    jsonArchive >> config;

    mView = std::make_shared<UISlotContainer>(config.EmptyImagePath, config.ItemsCount, config.ItemSize, aRenderer);
    mView->setPosition(Position(400, 0));
    for(size_t i = 0; i < count; ++i)
    {
        std::string aItemPath = "GameData/textures/items/"
                + mModel->getItemFromIndex(i)->getCaption() + ".png";
        mView->LoadItemAtIndex(aItemPath, i);
        // TODO normal positions
        auto pos = config.ItemsPositions[i];
//        pos.x += 300;
        mView->SetItemPos(pos, i);
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
