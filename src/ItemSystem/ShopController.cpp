/*
 * ShopController.cpp
 *
 *  Created on: 20 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "ShopController.h"
//#include "../GraphicsSystem/ShopItemUI.h"
#include "../Grouping/FontManager.h"
#include "../GraphicsSystem/newSystem/UIElement/ConcreteComposite.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImage.h"
//#include "../GraphicsSystem/newSystem/UIElement/UILabel.h"
#include "../GraphicsSystem/newSystem/UIElement/UITextButton.h"

ShopController::ShopController()
: model(nullptr), view(nullptr)
{
	// TODO Auto-generated constructor stub

}

void ShopController::setView(std::shared_ptr<UIScrollList> &newView)
{
    view = newView;
}


void ShopController::setModel(std::shared_ptr<ShopInventory> newModel)
{
	model = newModel;
}

std::shared_ptr<ShopInventory> ShopController::getModel() const
{
	return model;
}

void ShopController::initView(std::shared_ptr<RenderingSystem>& aRenderer)
{

	int count = model->getItemCount();
	std::cout << "ItemCount = " << count << std::endl;

    Font aFont =  FontManager::getInstance()->getFontByKind2("ButtonFont");

	for(int i = 0; i != count; ++i)
	{
        auto shopItem = std::make_shared<ConcreteComposite>(aRenderer);
        shopItem->setSize(Size(250, 160));

        auto shopItemGroup = std::make_shared<ConcreteComposite>(aRenderer);
        shopItemGroup->setSize(Size(shopItem->getSize().width, 80));

        auto shopItemIcon = std::make_shared<UIImage>(aRenderer);
        string iconPath = "GameData/textures/items/" +
                model->getItemFromIndex(i)->getCaption() + ".png";
        shopItemIcon->loadTexture(iconPath);
        shopItemIcon->setSize(Size(50,50));
        shopItemGroup->addChild(shopItemIcon);

        auto shopItemCaption = std::make_shared<UILabel>(model->getItemFromIndex(i)->getCaption() , aFont, aRenderer);
        shopItemCaption->setPosition(shopItemGroup->getNextPosition());
        shopItemGroup->addChild(shopItemCaption);

        auto shopItemDescription = std::make_shared<UILabel>(model->getItemFromIndex(i)->getDescription() , aFont, aRenderer);
        Position descPos{shopItemCaption->getLocalPosition().x, shopItemGroup->getNextVerticalPosition().y};
        shopItemDescription->setPosition(descPos);
        shopItemGroup->addChild(shopItemDescription);

        shopItem->addChild(shopItemGroup);

        string priceText = std::to_string(model->getItemFromIndex(i)->getPrice());
        auto shopItemPrice = std::make_shared<UILabel>(priceText , aFont, aRenderer);
        shopItemPrice->setPosition(shopItem->getNextVerticalPosition());

        shopItem->addChild(shopItemPrice);

        auto shopItemBuyButton = std::make_shared<UITextButton>("Купить" , aFont, aRenderer);
        shopItemBuyButton->setPosition(Position(shopItem->getNextPosition().x, shopItemPrice->getPosition().y));

        shopItem->addChild(shopItemBuyButton);

        view->addChild(shopItem);
	}
    view->ConnectMethod(std::bind( &ShopController::sendItemToModel, this, std::placeholders::_1) );
}

bool ShopController::sendItemToModel(int index)
{
    if (model == nullptr)
        return false;
    return model->sendItem(index);
}
