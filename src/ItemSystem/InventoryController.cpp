/*
 * InventoryController.cpp
 *
 *  Created on: 24 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "InventoryController.h"
//#include "../GraphicsSystem/UI/TextButton.h"
//#include "../GraphicsSystem/ShopItemUI.h"
#include "../Grouping/FontManager.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImage.h"
//#include "../GraphicsSystem/newSystem/UIElement/UILabel.h"
#include "../GraphicsSystem/newSystem/UIElement/UITextButton.h"

InventoryController::InventoryController(std::shared_ptr<RenderingSystem>& aRenderer)
: model(nullptr), view(nullptr), renderer(aRenderer), arial()
{
}

InventoryController::~InventoryController()
{
}

void InventoryController::setView(std::shared_ptr<UIScrollList>& newView)
{
	view = newView;
}

void InventoryController::setModel(std::shared_ptr<Inventory> newModel)
{
	model = newModel;
}

std::shared_ptr<Inventory> InventoryController::getModel() const
{
	return model;
}

void InventoryController::initView()
{
    arial.loadFromFile("Fonts/arial.ttf", 20);

    view->ConnectMethod(std::bind( &InventoryController::sendItemToModel, this, std::placeholders::_1) );
    model->ConnectControllerReceiver(std::bind( &InventoryController::receiveItemFromModel, this, std::placeholders::_1, std::placeholders::_2) );

	int count = model->getItemCount();
	if (count == 0)
		return;


	std::cout << "ItemCount = " << count << std::endl;

    Font aFont =  FontManager::getInstance()->getFontByKind2("ButtonFont");
    for(int i = 0; i != count; ++i)
	{

        auto shopItemGroup = std::make_shared<ConcreteComposite>(renderer);
        shopItemGroup->setSize(Size(150, 80));

        auto shopItemIcon = std::make_shared<UIImage>(renderer);
        string iconPath = "GameData/textures/items/" +
                model->getItemFromIndex(i)->getCaption() + ".png";
        shopItemIcon->loadTexture(iconPath);
        shopItemIcon->setSize(Size(50,50));
        shopItemGroup->addChild(shopItemIcon);

        auto shopItemCaption = std::make_shared<UILabel>(model->getItemFromIndex(i)->getCaption() , aFont, renderer);
        shopItemCaption->setPosition(shopItemGroup->getNextPosition());
        shopItemGroup->addChild(shopItemCaption);

        auto shopItemDescription = std::make_shared<UILabel>(model->getItemFromIndex(i)->getDescription() , aFont, renderer);
        Position descPos{shopItemCaption->getLocalPosition().x, shopItemGroup->getNextVerticalPosition().y};
        shopItemDescription->setPosition(descPos);
        shopItemGroup->addChild(shopItemDescription);

        view->addChild(shopItemGroup);
	}

}

void InventoryController::receiveItemFromModel(string caption, size_t itemType)
{
    if (caption.empty())
        return;

    Font aFont =  FontManager::getInstance()->getFontByKind2("ButtonFont");

    auto shopItemGroup = std::make_shared<ConcreteComposite>(renderer);
    shopItemGroup->setSize(Size(150, 80));

    auto shopItemIcon = std::make_shared<UIImage>(renderer);
    string iconPath = "GameData/textures/items/" +
           caption + ".png";
    shopItemIcon->loadTexture(iconPath);
    shopItemIcon->setSize(Size(50,50));
    shopItemGroup->addChild(shopItemIcon);

    auto shopItemCaption = std::make_shared<UILabel>(caption , aFont, renderer);
    shopItemCaption->setPosition(shopItemGroup->getNextPosition());
    shopItemGroup->addChild(shopItemCaption);

    auto shopItemDescription = std::make_shared<UILabel>("descr stub", aFont, renderer);
    Position descPos{shopItemCaption->getLocalPosition().x, shopItemGroup->getNextVerticalPosition().y};
    shopItemDescription->setPosition(descPos);
    shopItemGroup->addChild(shopItemDescription);

    view->addChild(shopItemGroup);

}

bool InventoryController::sendItemToModel(int index)
{

   return model->sendItem(index);

}
