/*
 * ShopScene.cpp
 *
 *  Created on: 20 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "ShopScene.h"
#include "../GlobalScripts/GameModel.h"
#include "../GlobalScripts/AccountModel.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImage.h"
#include "../GraphicsSystem/newSystem/UIElement/UILabel.h"

ShopScene::ShopScene(std::shared_ptr<RenderingSystem> &aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher)
    : Scene(aRenderer, aInputDispatcher)
    , goldCoinsLabel(nullptr)
    , shopController(nullptr)
{

}

ShopScene::~ShopScene()
{
    clear();
}

void ShopScene::init(std::shared_ptr<SceneManager> sceneManagerPtr)
{
    renderer->setRendererDrawColor(255, 255, 255, 255);

    Scene::init(sceneManagerPtr);

    initBackGroundUI();
    initShopItemsUI();
    std::cout << "KU-KU" << std::endl;
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
        string sss1 = std::to_string(AccountModel::getInstance()->getGoldAmount());
        goldCoinsLabel->setText(sss1);
    }
}

void ShopScene::initControlButton()
{
    Scene::addLoadSceneButton("Назад", "ButtonFont", "MainScene",
                MainRect->getSize().width - 100, MainRect->getSize().height - 50,
                              100, 50);
}

void ShopScene::initBackGroundUI()
{

    auto backGroundImage = std::make_shared<UIImage>(renderer);
    backGroundImage->loadTexture("GameData/textures/shopBackground.jpg");
    backGroundImage->setSize(Size(MainRect->getSize().width*3/5, MainRect->getSize().height - 50));
    MainRect->addChild(backGroundImage);

    Font aFont = FontManager::getInstance()->getFontByKind2("ButtonFont");


    class UIClickLabel : public UILabel, public InputHandler
    {
    public:
        UIClickLabel(const string& ltext, const Font& lfont, std::shared_ptr<RenderingSystem>& aRenderingContext)
            :UILabel(ltext, lfont, aRenderingContext)
        {

        }
        ~UIClickLabel() = default;

        UIClickLabel() = default;

        bool onClick(Position point) override
        {
            auto pointCoords = "OnClick pount Coords = " + std::to_string(point.x) + ";" + std::to_string(point.y);
            setText(pointCoords);
            return false;
        }

        bool canDrag() const override
        {
            return true;
        }

        virtual bool onDrag(int dy) override
        {
            auto pointCoords = "OnDrag value = " +  std::to_string(dy);
            setText(pointCoords);

            return false;
        }

        bool containsPoint(int, int) const override
        {
            return true;
        }
    };

    auto touchLabel = std::make_shared<UIClickLabel>("XXXXX", aFont, renderer);
    touchLabel->setPosition(Position(0, MainRect->getSize().height - 25));
    MainRect->addChild(touchLabel);


    auto sceneNameLabel = std::make_shared<UILabel>("Мистическая лавка", aFont, renderer);
    sceneNameLabel->setPosition(MainRect->getNextVerticalPosition());
    MainRect->addChild(sceneNameLabel);

    string goldAmount = std::to_string(AccountModel::getInstance()->getGoldAmount());

    goldCoinsLabel = std::make_shared<UILabel>(goldAmount, aFont, renderer);
    goldCoinsLabel->setPosition(Position(MainRect->getNextHorizontalPosition().x, sceneNameLabel->getPosition().y));
    MainRect->addChild(goldCoinsLabel);


//    goldCoins = new Label();
//    goldCoins->setFont(FontManager::getInstance()->getFontByKind("ButtonFont"));
//    string goldAmount = std::to_string(AccountModel::getInstance()->getGoldAmount());
//    goldCoins->setText(goldAmount);
//    goldCoins->setPos(Renderer::getInstance()->getScreenWidth() - 310, Renderer::getInstance()->getScreenHeight() - 50);

//    Scene::addToUIList(goldCoins);


    initControlButton();
}

void ShopScene::initShopItemsUI()
{

//    GameModel::getInstance()->loadShopItems("GameData/Items.xml");
    const int showItems = 3;

    auto scroll = std::make_shared<UIScrollList>(showItems, renderer);

    scroll->setSize(Size(MainRect->getSize().width*2/5, MainRect->getSize().height - 50));
    scroll->setPosition(Position(MainRect->getSize().width*3/5, 0));

    shopController = std::make_shared<ShopController>();
    if (shopController != nullptr)
    {
        shopController->setModel(GameModel::getInstance()->getShopInventory());
        shopController->setView(std::move(scroll));
        shopController->initView(renderer);
        MainRect->addChild(shopController->getView());
    }
}
