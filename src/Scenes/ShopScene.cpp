/*
 * ShopScene.cpp
 *
 *  Created on: 20 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "ShopScene.h"
#include "../GlobalScripts/GameModel.h"
#include "../GlobalScripts/AccountModel.h"
ShopScene::ShopScene()
    :shopController(nullptr)
   // :arialFont(new CFont())
{
	// TODO Auto-generated constructor stub

}

ShopScene::~ShopScene()
{
    clear();
}

void ShopScene::init(SceneManager* sceneManagerPtr)
{
    Renderer::getInstance()->setRendererDrawColor(255, 255, 255);

    Scene::init(sceneManagerPtr);
    initBackGroundUI();
    initShopItemsUI();
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
                Renderer::getInstance()->getScreenWidth() - 100, Renderer::getInstance()->getScreenHeight() - 50,
                              100, 50);
}

void ShopScene::initBackGroundUI()
{
    CTexture* backGround = new CTexture();
    backGround->loadTexture("GameData/textures/shopBackground.jpg");
    backGround->setRect(0, 0, Renderer::getInstance()->getScreenWidth()*0.6, Renderer::getInstance()->getScreenHeight() - 50);
    Scene::addToUIList(backGround);

    goldCoins = new Label();
    goldCoins->setFont(FontManager::getInstance()->getFontByKind("TextFont"));
    string goldAmount = std::to_string(AccountModel::getInstance()->getGoldAmount());
    goldCoins->setText(goldAmount);
    goldCoins->setPos(Renderer::getInstance()->getScreenWidth() - 100 - goldCoins->getRect().w - 10, Renderer::getInstance()->getScreenHeight() - 50);

    Scene::addToUIList(goldCoins);

    Label* sceneName = new Label();
    sceneName->setFont(FontManager::getInstance()->getFontByKind("TextFont"));
    string sceneNameString = "Мистическая лавка";
    sceneName->setText(sceneNameString);
    sceneName->setPos(goldCoins->getRect().x - sceneName->getRect().w -100, goldCoins->getRect().y);
    Scene::addToUIList(sceneName);

    initControlButton();
}

void ShopScene::initShopItemsUI()
{

    GameModel::getInstance()->loadShopItems("GameData/Items.xml");

        const int showItems = 5;
        const int itemWidth = 72;
        const int itemHeight = 72;

        ScrollList* scroll =  new ScrollList();
        scroll->initScrollList(showItems, itemWidth, itemHeight);
        scroll->setRect(Renderer::getInstance()->getScreenWidth()*0.6, 0, Renderer::getInstance()->getScreenWidth()*0.4, Renderer::getInstance()->getScreenHeight() - 50);
        scroll->loadTexture("GameData/textures/topPanel.png");

        shopController = new ShopController();
        shopController->setModel(GameModel::getInstance()->getShopInventory());

        shopController->setView(scroll);
        shopController->initView();

        Scene::addToUIList(scroll);


}
