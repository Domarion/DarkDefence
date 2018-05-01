#include "ShopScene.h"
#include "../GlobalScripts/GameModel.h"
#include "../GlobalScripts/AccountModel.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImage.h"
#include "../GraphicsSystem/newSystem/UIElement/UILabel.h"
#include "../GraphicsSystem/newSystem/VerticalLayout.h"
#include "../GlobalScripts/ResourceManager.h"

ShopScene::ShopScene(std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher)
    : Scene(aRenderer, aInputDispatcher)
{
}

void ShopScene::init()
{
    renderer->setRendererDrawColor(255, 255, 255, 255);

    Scene::init();

    initBackGroundUI();
    initShopItemsUI();
    Scene::addToUIList(MainRect);
}

void ShopScene::clear()
{
    Scene::clear();
    shopController.reset();
    goldCoinsLabel.reset();

    GameModel::getInstance()->getShopInventory()->clearControllerReceivers();
}

void ShopScene::startUpdate(double timestep)
{
    if (goldCoinsLabel != nullptr)
    {
        Scene::startUpdate(timestep);
        string goldAmountText = std::to_string(AccountModel::getInstance()->getGoldAmount());
        goldCoinsLabel->setText(goldAmountText);
    }
}

void ShopScene::initControlButton()
{
    Scene::addLoadSceneButton(
        "Назад", "ButtonFont", "MainScene", MainRect->getSize().width - 100, MainRect->getSize().height - 50, 100, 50);
}

void ShopScene::initBackGroundUI()
{
    auto backGroundImage = std::make_shared<UIImage>(renderer);
    backGroundImage->setTexture(ResourceManager::getInstance()->getTexture("ShopSceneBackground"));
    MainRect->addChild(backGroundImage);
    backGroundImage->setSize(MainRect->getSize());

    const auto& font = FontManager::getInstance()->getFontByKind2("ButtonFont");

    auto sceneNameLabel = std::make_shared<UILabel>("Мистическая лавка", font, renderer);
    sceneNameLabel->setPosition(MainRect->getNextVerticalPosition());
    MainRect->addChild(sceneNameLabel);

    string goldAmount = std::to_string(AccountModel::getInstance()->getGoldAmount());

    goldCoinsLabel = std::make_shared<UILabel>(goldAmount, font, renderer);
    goldCoinsLabel->setPosition(Position(MainRect->getNextHorizontalPosition().x, sceneNameLabel->getPosition().y));
    MainRect->addChild(goldCoinsLabel);

    initControlButton();
}

void ShopScene::initShopItemsUI()
{
    const int showItems = 5;

    auto layout = std::make_shared<VerticalLayout>();
    auto scroll = std::make_shared<UIScrollList>(showItems, renderer, layout);

    scroll->setSize(Size(MainRect->getSize().width*3/5, MainRect->getSize().height - 50));
    scroll->setPosition(Position(MainRect->getSize().width*5/7, 50));

    shopController = std::make_shared<ShopController>();
    if (shopController != nullptr)
    {
        shopController->setModel(GameModel::getInstance()->getShopInventory());
        shopController->setView(std::move(scroll));
        shopController->initView(renderer);
        MainRect->addChild(shopController->getView());
    }
}
