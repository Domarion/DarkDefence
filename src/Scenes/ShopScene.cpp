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

ShopScene::ShopScene(std::shared_ptr<RenderingSystem> &aRenderer)
    :Scene(aRenderer)
    , shopController(nullptr)
{

}

ShopScene::~ShopScene()
{
    clear();
}

void ShopScene::init(SceneManager* sceneManagerPtr)
{
    renderer->setRendererDrawColor(255, 255, 255, 255);

    Scene::init(sceneManagerPtr);
    initBackGroundUI();
    initShopItemsUI();
    Scene::addToUIList(MainRect);
}

void ShopScene::clear()
{
    goldCoins = nullptr;

    Scene::clear();
    delete shopController;
}


void ShopScene::startUpdate(double timestep)
{
    if (goldCoins != nullptr)
    {
        Scene::startUpdate(timestep);
        string sss1 = std::to_string(AccountModel::getInstance()->getGoldAmount());
        goldCoins->setText(sss1);
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
    auto sceneNameLabel = std::make_shared<UILabel>("Мистическая лавка", aFont, renderer);
    sceneNameLabel->setPosition(MainRect->getNextVerticalPosition());
    MainRect->addChild(sceneNameLabel);

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

    GameModel::getInstance()->loadShopItems("GameData/Items.xml");

//        const int showItems = 5;
//        const int itemWidth = 72;
//        const int itemHeight = 72;

//        ScrollList* scroll =  new ScrollList();
//        scroll->initScrollList(showItems, itemWidth, itemHeight);
//        scroll->setRect(Renderer::getInstance()->getScreenWidth()*0.6, 0, Renderer::getInstance()->getScreenWidth()*0.4, Renderer::getInstance()->getScreenHeight() - 50);
//        scroll->loadTexture("GameData/textures/topPanel.png");

//        shopController = new ShopController();
//        shopController->setModel(GameModel::getInstance()->getShopInventory());

//        shopController->setView(scroll);
//        shopController->initView();

//        Scene::addToUIList(scroll);


}
