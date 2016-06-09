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
   // :arialFont(new CFont())
{
	// TODO Auto-generated constructor stub

}

InventoryScene::~InventoryScene()
{
	// TODO Auto-generated destructor stub
}

void InventoryScene::initScene( SceneManager* sceneManagerPtr)
{

     Renderer::getInstance()->setRendererDrawColor(255, 255, 255);
	if (wasInited == false)
    {
        Scene::initScene(sceneManagerPtr);
        std::cout << "ShopScene" << std::endl;


        //GameModel::getInstance()->loadShopItems("GameData/Items.xml");

        //arialFont.get()->loadFromFile("Fonts/arial.ttf", 24);


        button.setFont(FontManager::getInstance()->getFontByKind("ButtonFont"));
        button.setRect(Renderer::getInstance()->getScreenWidth() - 100, Renderer::getInstance()->getScreenHeight() - 50, 100, 50);
        button.setText("Назад");
        string s1 = "MainScene";
        button.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s1));
        listGUI.push_back(&button);

        heroFigure.setRect(300,0, 300, 500);
        heroController.setModel(GameModel::getInstance()->getHeroInventory());
        heroController.setView(&heroFigure);
        heroController.initView();

        listGUI.push_back(&heroFigure);
    }

    if (GameModel::getInstance()->getInventory()->getItemCount() > 0)
    {
        const int showItems = 5;
        const int itemWidth = 72;
        const int itemHeight = 72;
        scroll.clear();
        scroll.initScrollList(showItems, itemWidth, itemHeight);
        scroll.setRect(0, 0, Renderer::getInstance()->getScreenWidth()*0.4, Renderer::getInstance()->getScreenHeight() - 50);
        scroll.loadTexture("GameData/textures/topPanel.png");

        inventoryController.setModel(GameModel::getInstance()->getInventory());


        inventoryController.setView(&scroll);
        inventoryController.initView();

        listGUI.push_back(&scroll);
    }



    InputDispatcher::getInstance()->addHandler(&scroll);
    InputDispatcher::getInstance()->addHandler(&heroFigure);
    InputDispatcher::getInstance()->addHandler(&button);


}

void InventoryScene::finalizeScene()
{
    Scene::finalizeScene();
}



void InventoryScene::startUpdate(double timestep)
{
    Scene::startUpdate(timestep);
}

