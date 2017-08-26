/*
 * ShopController.cpp
 *
 *  Created on: 20 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "ShopController.h"
#include "../Grouping/FontManager.h"
#include "../GraphicsSystem/newSystem/UIElement/ConcreteComposite.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImage.h"
#include "../GraphicsSystem/newSystem/UIElement/UITextButton.h"
#include "../GraphicsSystem/newSystem/StubLayout.h"
#include "../GraphicsSystem/newSystem/VerticalLayout.h"
#include "../GraphicsSystem/newSystem/HorizontalLayout.h"

void ShopController::setView(std::shared_ptr<UIScrollList>&& newView)
{
    view = std::move(newView);
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

    Font aFont =  FontManager::getInstance()->getFontByKind2("ButtonFont");

    Size itemSize{view->getSize()};

    auto horizontalLayout = std::make_shared<HorizontalLayout>();

    itemSize.height /= view->getItemCountToShow() + 1;
    for(int i = 0; i < count; ++i)
	{
        auto shopItemGroup = std::make_shared<ConcreteComposite>(aRenderer, horizontalLayout);
        shopItemGroup->setSize(itemSize);

        auto shopItemIcon = std::make_shared<UIImage>(aRenderer);
        string iconPath = "GameData/textures/items/" +
                model->getItemFromIndex(i)->getCaption() + ".png";
        shopItemIcon->loadTexture(iconPath);
        shopItemIcon->setSize(Size(itemSize.height, itemSize.height));
        shopItemGroup->addChild(shopItemIcon);

        auto shopItemCaption = std::make_shared<UILabel>(model->getItemFromIndex(i)->getCaption() , aFont, aRenderer);
        shopItemCaption->setPosition(shopItemGroup->getNextHorizontalPosition());
        shopItemGroup->addChild(shopItemCaption);

        string priceText = std::to_string(model->getItemFromIndex(i)->getPrice());
        auto shopItemPrice = std::make_shared<UILabel>(priceText , aFont, aRenderer);

        shopItemGroup->addChild(shopItemPrice);

        auto shopItemBuyButton = std::make_shared<UITextButton>("Купить" , aFont, aRenderer);
        shopItemGroup->addChild(shopItemBuyButton);

        view->addChild(shopItemGroup);
	}

    view->ConnectMethod(std::bind( &ShopController::sendItemToModel, this, std::placeholders::_1) );
}

bool ShopController::sendItemToModel(int index)
{
    if (model == nullptr)
        return false;
    return model->sendItem(index);
}

std::shared_ptr<UIScrollList> ShopController::getView() const
{
    return view;
}
