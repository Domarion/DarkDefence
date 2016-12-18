/*
 * HeroInventoryController.cpp
 *
 *  Created on: 28 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "HeroInventoryController.h"
//#include "../GraphicsSystem/UI/TextButton.h"
HeroInventoryController::HeroInventoryController()
    : model(nullptr)
    , view(nullptr)
    , slotsPositions()
{
}

HeroInventoryController::~HeroInventoryController()
{
    view = nullptr;
}

void HeroInventoryController::setView(std::shared_ptr<UISlotContainer> newView)
{
	view = newView;
}

std::shared_ptr<UISlotContainer> HeroInventoryController::getView() const
{
	return view;
}

void HeroInventoryController::setModel(std::shared_ptr<HeroInventory> newModel)
{
	model = newModel;
}

std::shared_ptr<HeroInventory> HeroInventoryController::getModel() const
{
    return model;
}

void HeroInventoryController::initLocalPositions(Size aRectSize)
{
    if (model == nullptr)
        return;

    size_t count = model->getItemCount();
    slotsPositions.resize(count);
    Size itemSize(50, 50);
    int centerHorizontal{(aRectSize.width - itemSize.width)/2};
    int y = 0;


    for(size_t i = 0; i < count; ++i)
    {
       slotsPositions[i] = Position(centerHorizontal, y);
       y += itemSize.height;
    }
   // slotsPositions[0] = centerHorizontal;
    //    int centerX = view->getRect().x + static_cast<int>(view->getRect().w * 0.5) +itemWidth;
    //    int y = 0;
    //    view->setItemRect(0, centerX, y, itemWidth, itemHeight);
    //    y += itemHeight;

    //    view->setItemRect(1, centerX, y, itemWidth, itemHeight);
    //     y += itemHeight;

    //    view->setItemRect(2, centerX - itemWidth, y, itemWidth, itemHeight);
    //    view->setItemRect(3, centerX, y, itemWidth, itemHeight);
    //    view->setItemRect(4, centerX + itemWidth, y, itemWidth, itemHeight);

    //    view->setItemRect(5, centerX - 2*itemWidth, y - itemHeight, itemWidth, itemHeight);

    //    y += itemHeight;

    //    view->setItemRect(6, centerX, y, itemWidth, itemHeight);
    //   // y += itemHeight;
    //    view->setItemRect(7, centerX + 2*itemWidth, y, itemWidth, itemHeight);
    //    view->setItemRect(8, centerX + 3*itemWidth, y, itemWidth, itemHeight);
}

void HeroInventoryController::initView(std::shared_ptr<RenderingSystem> &aRenderer)
{
    if (model == nullptr)
        return;

    size_t count = model->getItemCount();

    if (count == 0)
        return;

    std::string emptySlotPath = "GameData/textures/EmptySlot.png";
    Size itemSize(50, 50);
    view = std::make_shared<UISlotContainer>(emptySlotPath, count, itemSize, aRenderer);

    for(size_t i = 0; i < count; ++i)
    {
        std::string aItemPath = "GameData/textures/items/"
                + model->getItemFromIndex(i)->getCaption() + ".png";
        view->LoadItemAtIndex(aItemPath, i);
        view->SetItemPos(slotsPositions[i], i);

    }
    view->ConnectMethod(std::bind( &HeroInventory::sendItem, model, std::placeholders::_1) );
    model->ConnectControllerReceiver(std::bind( &HeroInventoryController::receiveItemFromModel, this, std::placeholders::_1, std::placeholders::_2) );

}


void HeroInventoryController::receiveItemFromModel(string caption, size_t itemType)
{
    if (caption.empty())
        return;

    std::string imgPath = "GameData/textures/items/" + caption + ".png";
    view->LoadItemAtIndex(imgPath, itemType);

}
