/*
 * MainScene.cpp
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#include "MainScene.h"
#include "../GraphicsSystem/UI/Label.h"
#include <iostream>
#include "../Input/InputDispatcher.h"

MainScene::MainScene()
    :arialFont(nullptr)

{
	// TODO Auto-generated constructor stub
}

MainScene::~MainScene()
{
	// TODO Auto-generated destructor stub
	//listGUI.clear();
    TTF_CloseFont(arialFont);
}


void MainScene::finalizeScene()
{
	Scene::finalizeScene();
	//listGUI.clear();

}

void MainScene::loadScene()
{
}

void MainScene::unloadScene()
{
}


void MainScene::initScene(SceneManager* sceneManagerPtr)
{


    Renderer::getInstance()->setRendererDrawColor(255, 255, 255);
	std::cout << "WhereAreYou" << std::endl;

	if (wasInited == false)
	{
        Scene::initScene(sceneManagerPtr);

        backGround.setTexture(Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/castle.jpg"));
        backGround.setRect(0, 0, Renderer::getInstance()->getScreenWidth(), Renderer::getInstance()->getScreenHeight());
        listGUI.push_back(&backGround);

        arialFont = Renderer::getInstance()->loadFontFromFile("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 48);
        SDL_Color arialFontColor = {0, 0, 0};
        button.setFont(arialFont, arialFontColor);
        int x = Renderer::getInstance()->getScreenWidth()/4;
        int y = Renderer::getInstance()->getScreenHeight()/4;

        button.setRect(x, y, 200, 50);
        button.setText("Начать игру");
        string s1 = "MapMenuScene";
        button.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s1));
        y += 96;

        listGUI.push_back(&button);

        button2.setFont(arialFont, arialFontColor);


        button2.setRect(x, y, 200, 50);
        button2.setText("Магазин");
        string s2 = "ShopScene";
        button2.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s2));
         y += 96;

        listGUI.push_back(&button2);

        button3.setFont(arialFont, arialFontColor);
        button3.setRect(x, y, 200, 50);
        button3.setText("Инвентарь");
        string s3 = "InventoryScene";
        button3.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s3));


        listGUI.push_back(&button3);

	}
	else
	{
		std::cout << listGUI.size() << std::endl;
	}
	InputDispatcher::getInstance()->addHandler(&button);
	InputDispatcher::getInstance()->addHandler(&button2);
	InputDispatcher::getInstance()->addHandler(&button3);
}

void MainScene::startUpdate(double timestep)
{
    Scene::startUpdate(timestep);

}



