/*
 * ShopScene.cpp
 *
 *  Created on: 20 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "ShopScene.h"
#include "../GlobalScripts/GameModel.h"
#include "../Input/InputDispatcher.h"
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

	if (wasInited == false)
	{
        Scene::initScene(sceneManagerPtr);
        std::cout << "ShopScene" << std::endl;


        GameModel::getInstance()->loadShopItems("/home/kostya_hm/Projects/DarkDefence/GameData/Items.xml");

        const int showItems = 5;
        const int itemWidth = 72;
        const int itemHeight = 72;
        scroll.initScrollList(showItems, itemWidth, itemHeight);

        shopController.setModel(GameModel::getInstance()->getShopInventory());


        shopController.setView(&scroll);
        shopController.initView();

        listGUI.push_back(&scroll);


        TTF_Font* arialFont = Renderer::getInstance()->loadFontFromFile("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 24);
        SDL_Color arialFontColor = {255, 255, 255};

        button.setFont(arialFont, arialFontColor);
        button.setRect(200, 50, 150, 50);
        button.setText("Назад");
        string s1 = "MainScene";
        button.ConnectMethod(std::bind(&ShopScene::LoadSceneByName, this, s1));

        listGUI.push_back(&button);
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
}
void ShopScene::LoadSceneByName(string sceneName)
{
	parentSceneManager->setCurrentSceneByName(sceneName);

}
