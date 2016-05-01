/*
 * MainScene.cpp
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#include "MainScene.h"
#include "../Grouping/Scene.h"
#include "../GraphicsSystem/UI/Label.h"
#include <iostream>
#include "../Input/InputDispatcher.h"

MainScene::MainScene()

{
	// TODO Auto-generated constructor stub
}

MainScene::~MainScene()
{
	// TODO Auto-generated destructor stub
	//listGUI.clear();
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

	std::cout << "WhereAreYou" << std::endl;
	if (wasInited == false)
	{
        Scene::initScene(sceneManagerPtr);
        TTF_Font* arialFont = Renderer::getInstance()->loadFontFromFile("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 24);
        SDL_Color arialFontColor = {255, 255, 255};
        button.setFont(arialFont, arialFontColor);

        button.setRect(0, 50, 200, 50);
        button.setText("Начать игру");
        string s1 = "GameScene";
        button.ConnectMethod(std::bind(&MainScene::LoadSceneByName, this, s1));


        listGUI.push_back(&button);

        button2.setFont(arialFont, arialFontColor);


        button2.setRect(0, 100, 200, 50);
        button2.setText("Лавка");
        string s2 = "ShopScene";
        button2.ConnectMethod(std::bind(&MainScene::LoadSceneByName,  this, s2));


        listGUI.push_back(&button2);

        button3.setFont(arialFont, arialFontColor);
        button3.setRect(0, 150, 200, 50);
        button3.setText("Инвентарь");
        string s3 = "InventoryScene";
        button3.ConnectMethod(std::bind(&MainScene::LoadSceneByName,  this, s3));


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


void MainScene::LoadSceneByName(string sceneName)
{
	parentSceneManager->setCurrentSceneByName(sceneName);

}
