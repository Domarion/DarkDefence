#include "ShopController.h"
#include "../Grouping/FontManager.h"
#include "../GraphicsSystem/newSystem/UIElement/ConcreteComposite.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImageButton.h"
#include "../GraphicsSystem/newSystem/UIElement/UITextButton.h"
#include "../GraphicsSystem/newSystem/StubLayout.h"
#include "../GraphicsSystem/newSystem/VerticalLayout.h"
#include "../GraphicsSystem/newSystem/HorizontalLayout.h"
#include "../GlobalScripts/ResourceManager.h"

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

    const Font& font =  FontManager::getInstance()->getFontByKind2("ItemFont");

    Size itemSize{view->getSize()};

    auto stubLayout = std::make_shared<StubLayout>();
    auto& buyButtonTexture = ResourceManager::getInstance()->getTexture("BuyButton");
    auto& goldCoinTexture = ResourceManager::getInstance()->getTexture("Gold");

    itemSize.height /= view->getItemCountToShow() + 1;
    for(int i = 0; i < count; ++i)
	{
        auto shopItemGroup = std::make_shared<ConcreteComposite>(aRenderer, stubLayout);
        shopItemGroup->setSize(itemSize);

        auto shopItemIcon = std::make_shared<UIImage>(aRenderer);
        string iconPath = "GameData/textures/items/" +
                model->getItemFromIndex(i)->getCaption() + ".png";
        shopItemIcon->loadTexture(iconPath);
        auto iconSize = Size(itemSize.height, itemSize.height);
        shopItemIcon->setSize(iconSize);
        shopItemGroup->addChild(shopItemIcon);

        auto shopItemCaption = std::make_shared<UILabel>(model->getItemFromIndex(i)->getCaption(), font, aRenderer);
        shopItemCaption->setPosition(shopItemGroup->getNextHorizontalPosition());
        shopItemGroup->addChild(shopItemCaption);

        Position pricePos(shopItemIcon->getSize().width, shopItemGroup->getNextVerticalPosition().y);

        auto goldCoin = std::make_shared<UIImage>(aRenderer);
        goldCoin->setTexture(goldCoinTexture);
        goldCoin->setPosition(pricePos);
        goldCoin->setSize(iconSize / 2);
        shopItemGroup->addChild(goldCoin);

        pricePos.x = shopItemGroup->getNextHorizontalPosition().x;
        string priceText = std::to_string(model->getItemFromIndex(i)->getPrice());
        auto shopItemPrice = std::make_shared<UILabel>(priceText, font, aRenderer);
        shopItemPrice->setPosition(pricePos);
        shopItemGroup->addChild(shopItemPrice);

        auto shopItemBuyButton = std::make_shared<UIImageButton>(aRenderer);
        pricePos.x = shopItemGroup->getNextHorizontalPosition().x;
        shopItemBuyButton->setTexture(buyButtonTexture);
        shopItemBuyButton->setPosition(pricePos);
        shopItemBuyButton->setSize(iconSize / 2);

        shopItemGroup->addChild(shopItemBuyButton);

        view->addChild(shopItemGroup);
	}

    view->ConnectMethod(std::bind(&ShopController::sendItemToModel, this, std::placeholders::_1));
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
