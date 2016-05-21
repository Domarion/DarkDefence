/*
 * ShopScene.cpp
 *
 *  Created on: 20 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "ShopScene.h"
#include "../GlobalScripts/GameModel.h"
#include "../Input/InputDispatcher.h"
#include "../GlobalScripts/AccountModel.h"
ShopScene::ShopScene()
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
        backGround.setTexture(Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/shopBackground.jpg"));
        backGround.setRect(0, 0, Renderer::getInstance()->getScreenWidth()*0.6, Renderer::getInstance()->getScreenHeight() - 50);
        listGUI.push_back(&backGround);

        GameModel::getInstance()->loadShopItems("/home/kostya_hm/Projects/DarkDefence/GameData/Items.xml");

        const int showItems = 5;
        const int itemWidth = 72;
        const int itemHeight = 72;
        scroll.initScrollList(showItems, itemWidth, itemHeight);
        scroll.setRect(Renderer::getInstance()->getScreenWidth()*0.6, 0, Renderer::getInstance()->getScreenWidth()*0.4, Renderer::getInstance()->getScreenHeight() - 50);
        scroll.setTexture(Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/topPanel.png"));
        shopController.setModel(GameModel::getInstance()->getShopInventory());


        shopController.setView(&scroll);
        shopController.initView();

        listGUI.push_back(&scroll);


        TTF_Font* arialFont = Renderer::getInstance()->loadFontFromFile("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 24);
        SDL_Color arialFontColor = {0, 0, 0};

        button.setFont(arialFont, arialFontColor);
        button.setRect(Renderer::getInstance()->getScreenWidth() - 100, Renderer::getInstance()->getScreenHeight() - 50, 100, 50);
        button.setText("Назад");
        string s1 = "MainScene";
        button.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s1));

        listGUI.push_back(&button);

        goldCoins.setFont(arialFont, arialFontColor);
        string sss1 = std::to_string(AccountModel::getInstance()->getGoldAmount());
        goldCoins.setText(sss1);
        goldCoins.setPos(button.getRect().x - goldCoins.getRect().w - 10, button.getRect().y);

        listGUI.push_back(&goldCoins);

        sceneName.setFont(arialFont, arialFontColor);
        string sss2 = "Мистическая лавка";
        sceneName.setText(sss2);
        sceneName.setPos(goldCoins.getRect().x - sceneName.getRect().w -100, goldCoins.getRect().y);
        listGUI.push_back(&sceneName);

	}
	InputDispatcher::getInstance()->addHandler(&scroll);
	InputDispatcher::getInstance()->addHandler(&button);
}

void ShopScene::finalizeScene()
{
	Scene::finalizeScene();
}

void ShopScene::loadScene()
{
}

void ShopScene::unloadScene()
{
}

void ShopScene::startUpdate(double timestep)
{
	Scene::startUpdate(timestep);
    string sss1 = std::to_string(AccountModel::getInstance()->getGoldAmount());
    goldCoins.setText(sss1);
}
