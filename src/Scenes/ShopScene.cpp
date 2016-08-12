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
   // :arialFont(new CFont())
{
	// TODO Auto-generated constructor stub

}

ShopScene::~ShopScene()
{
	// TODO Auto-generated destructor stub
}

void ShopScene::initScene(SceneManager* sceneManagerPtr)
{
    Renderer::getInstance()->setRendererDrawColor(255, 255, 255);
	if (wasInited == false)
	{
        Scene::initScene(sceneManagerPtr);
        std::cout << "ShopScene" << std::endl;
        backGround.loadTexture("GameData/textures/shopBackground.jpg");
        backGround.setRect(0, 0, Renderer::getInstance()->getScreenWidth()*0.6, Renderer::getInstance()->getScreenHeight() - 50);
        Scene::addToUIList(&backGround);

        GameModel::getInstance()->loadShopItems("GameData/Items.xml");

        const int showItems = 5;
        const int itemWidth = 72;
        const int itemHeight = 72;
        scroll.initScrollList(showItems, itemWidth, itemHeight);
        scroll.setRect(Renderer::getInstance()->getScreenWidth()*0.6, 0, Renderer::getInstance()->getScreenWidth()*0.4, Renderer::getInstance()->getScreenHeight() - 50);
        scroll.loadTexture("GameData/textures/topPanel.png");
        shopController.setModel(GameModel::getInstance()->getShopInventory());


        shopController.setView(&scroll);
        shopController.initView();

        Scene::addToUIList(&scroll);


        //arialFont.get()->loadFromFile("Fonts/arial.ttf", 24);


        button.setFont(FontManager::getInstance()->getFontByKind("ButtonFont"));
        button.setPos(Renderer::getInstance()->getScreenWidth() - 100, Renderer::getInstance()->getScreenHeight() - 50);
        button.setText("Назад");
        string s1 = "MainScene";
        button.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s1));

        Scene::addToUIList(&button);

        goldCoins.setFont(FontManager::getInstance()->getFontByKind("TextFont"));
        string sss1 = std::to_string(AccountModel::getInstance()->getGoldAmount());
        goldCoins.setText(sss1);
        goldCoins.setPos(button.getRect().x - goldCoins.getRect().w - 10, button.getRect().y);

        Scene::addToUIList(&goldCoins);

        sceneName.setFont(FontManager::getInstance()->getFontByKind("TextFont"));
        string sss2 = "Мистическая лавка";
        sceneName.setText(sss2);
        sceneName.setPos(goldCoins.getRect().x - sceneName.getRect().w -100, goldCoins.getRect().y);
        Scene::addToUIList(&sceneName);

	}

}

void ShopScene::finalizeScene()
{
	Scene::finalizeScene();
}



void ShopScene::startUpdate(double timestep)
{
	Scene::startUpdate(timestep);
    string sss1 = std::to_string(AccountModel::getInstance()->getGoldAmount());
    goldCoins.setText(sss1);
}
