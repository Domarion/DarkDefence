/*
 * InventoryScene.cpp
 *
 *  Created on: 18 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "InventoryScene.h"
#include "../GlobalScripts/GameModel.h"
#include "../Input/InputDispatcher.h"

InventoryScene::InventoryScene()
{
	// TODO Auto-generated constructor stub

}

InventoryScene::~InventoryScene()
{
	// TODO Auto-generated destructor stub
}

void InventoryScene::initScene( SceneManager* sceneManagerPtr)
{
	if (wasInited == false)
    {
        Scene::initScene(sceneManagerPtr);
        std::cout << "ShopScene" << std::endl;


        GameModel::getInstance()->loadShopItems("/home/kostya_hm/Projects/DarkDefence/GameData/textures/items/Items.xml");

        const int showItems = 5;
        const int itemWidth = 72;
        const int itemHeight = 72;
        scroll.initScrollList(showItems, itemWidth, itemHeight);

        inventoryController.setModel(GameModel::getInstance()->getInventory());


        inventoryController.setView(&scroll);
        inventoryController.initView();

        listGUI.push_back(&scroll);

        TTF_Font* arialFont = Renderer::getInstance()->loadFontFromFile("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 24);
        SDL_Color arialFontColor = {255, 255, 255};

        button.setFont(arialFont, arialFontColor);
        button.setRect(200, 50, 150, 50);
        button.setText("Назад");
        string s1 = "MainScene";
        button.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s1));
        listGUI.push_back(&button);
    }

    InputDispatcher::getInstance()->addHandler(&scroll);
    InputDispatcher::getInstance()->addHandler(&button);
}

void InventoryScene::finalizeScene()
{
    Scene::finalizeScene();
}

void InventoryScene::loadScene()
{
}

void InventoryScene::unloadScene()
{
}

void InventoryScene::startUpdate(double timestep)
{
    Scene::startUpdate(timestep);
}

