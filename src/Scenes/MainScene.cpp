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


void MainScene::initScene(SDL_Renderer* renderer, SceneManager* sceneManagerPtr)
{

	std::cout << "WhereAreYou" << std::endl;
	if (wasInited == false)
	{
	Scene::initScene(renderer, sceneManagerPtr);
    /*labelText.loadFont("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 24);
	labelText.setRenderer(renderer);
	SDL_Rect* lrect = new SDL_Rect({0, 0, 200, 50});
	labelText.setRect(lrect);
	labelText.setText("Hello, Scene!!!");
	listGUI.push_back(&labelText);*/


    button.loadFont("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 24);
	button.setRenderer(renderer);
	SDL_Rect* lrect2 = new SDL_Rect({0, 50, 200, 50});
	button.setRect(lrect2);
	button.setText("Начать игру");
	string s1 = "GameScene";
	button.ConnectMethod(std::bind(&MainScene::LoadSceneByName, this, s1));


	listGUI.push_back(&button);

    button2.loadFont("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 24);
	button2.setRenderer(renderer);
	SDL_Rect* lrect3 = new SDL_Rect({0, 100, 200, 50});
	button2.setRect(lrect3);
	button2.setText("Лавка");
	string s2 = "ShopScene";
	button2.ConnectMethod(std::bind(&MainScene::LoadSceneByName,  this, s2));


	listGUI.push_back(&button2);

    button3.loadFont("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 24);
	button3.setRenderer(renderer);
	SDL_Rect* lrect4 = new SDL_Rect({0, 150, 200, 50});
	button3.setRect(lrect4);
	button3.setText("Инвентарь");
	string s3 = "InventoryScene";
	button3.ConnectMethod(std::bind(&MainScene::LoadSceneByName,  this, s3));


	listGUI.push_back(&button3);
	/*bar.setRenderer(renderer);
	bar.setRect(new SDL_Rect({0, 100, 200, 50}));
	SDL_Surface *surface1 = SDL_CreateRGBSurface(0,bar.getRect()->w, bar.getRect()->h, 16, 0, 0, 0, 0);
	//if (surface1 == nullptr)
		//std::cout << "fuck" << std::endl;
	SDL_Surface *surface2 = SDL_CreateRGBSurface(0,bar.getRect()->w, bar.getRect()->h, 16, 0, 0, 0, 0);
	//SDL_Texture *backTexture = SDL_CreateTextureFromSurface(bar.getRenderer(), surface1);
	//SDL_Texture *frontTexture = SDL_CreateTextureFromSurface(bar.getRenderer(), surface2);

	SDL_FillRect(surface1, nullptr, SDL_MapRGB(surface1->format, 150,100, 0));
	SDL_FillRect(surface2, nullptr, SDL_MapRGB(surface2->format, 200,100, 0));

	SDL_Texture  *backTexture = bar.getTextureFromSurface(surface1);
	SDL_Texture  *frontTexture = bar.getTextureFromSurface(surface2);
	SDL_FreeSurface(surface1);
	SDL_FreeSurface(surface2);
	bar.setTexture(backTexture);
	bar.setFrontTexture(frontTexture);
	backTexture = nullptr;
	frontTexture = nullptr;
	bar.calculateFront(100, 100);
	listGUI.push_back(&bar);
*/
	//parentSceneManager->setCurrentSceneByName("fff");
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
	/*static int temp = 100;
	static double currentval = 1000;
	currentval -= timestep;
	if (currentval <= 0 && temp > 0)
	{
		bar.calculateFront(temp, 100);
		currentval = 1000;
		--temp;
	}*/
}


void MainScene::LoadSceneByName(string sceneName)
{
	parentSceneManager->setCurrentSceneByName(sceneName);

}
