/*
 * GameScene.cpp
 *
 *  Created on: 4 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "GameScene.h"
#include <SDL2/SDL.h>
#include "../Mob/Mob.h"
#include <cmath>
#include "../GlobalScripts/GameModel.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
GameScene::GameScene()
:Scene(), gates()
{
	// TODO Auto-generated constructor stub

}

GameScene::~GameScene()
{
	// TODO Auto-generated destructor stub

    for(int i = 0; i != ResourcesModel::resourceTypeCount; ++i)
    {

        delete resourceLabels[i];
    }

}

void GameScene::initScene(SceneManager* sceneManagerPtr)
{

	if (!wasInited)
	{



        Scene::initScene(sceneManagerPtr);

        topPanel.setRect(0,0, 800, 40);
        topPanel.setTexture(Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/topPanel.png"));


        GameModel::getInstance()->getResourcesModel()->loadFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/resources.txt");


        gatesHealthBar.setRect(0, 0, 150, 20);

        SDL_Surface *surface1 = SDL_CreateRGBSurface(0, gatesHealthBar.getRect().w, gatesHealthBar.getRect().h, 16, 0, 0, 0, 0);
        SDL_Surface *surface2 = SDL_CreateRGBSurface(0, gatesHealthBar.getRect().w, gatesHealthBar.getRect().h, 16, 0, 0, 0, 0);

        SDL_FillRect(surface1, nullptr, SDL_MapRGB(surface1->format, 150,100, 0));
        SDL_FillRect(surface2, nullptr, SDL_MapRGB(surface2->format, 200,100, 0));

        SDL_Texture  *backTexture = Renderer::getInstance()->getTextureFromSurface(surface1);
        SDL_Texture  *frontTexture = Renderer::getInstance()->getTextureFromSurface(surface2);
        SDL_FreeSurface(surface1);
        SDL_FreeSurface(surface2);
        gatesHealthBar.setTexture(backTexture);
        gatesHealthBar.setFrontTexture(frontTexture);
        backTexture = nullptr;
        frontTexture = nullptr;
        gatesHealthBar.calculateFront(5000, 5000);
        topPanel.addChild(&gatesHealthBar);

        TTF_Font* arialFont = Renderer::getInstance()->loadFontFromFile("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 24);
        SDL_Color arialFontColor = {255, 255, 255};




        resourceLabels.resize(ResourcesModel::resourceTypeCount);
        for(int i = 0; i != ResourcesModel::resourceTypeCount; ++i)
        {
            string s = GameModel::getInstance()->getResourcesModel()->printResourceFromIndex(i);
            resourceLabels[i] = new Label();

            resourceLabels[i]->setFont(arialFont, arialFontColor);
            resourceLabels[i]->setText(s);

            resourceLabels[i]->setRect(0, 0, 120, 24);

            topPanel.addChild(resourceLabels[i]);
        }


        listGUI.push_back(&topPanel);



        GameModel::getInstance()->loadMonsterList("/home/kostya_hm/Projects/DarkDefence/GameData/MonsterList.xml");

        GameModel::getInstance()->loadTowerUpgrades("/home/kostya_hm/Projects/DarkDefence/GameData/TowerTree.xml");
        monsterSpawner.loadWavesInfo("/home/kostya_hm/Projects/DarkDefence/GameData/wavesInfo.txt");


        Terrain = objectFabric.produce("Terrain", "none", "/home/kostya_hm/Projects/DarkDefence/GameData/textures/terrain.JPG", 800, 600);
        spawnObject(0,0, Terrain);

        Mob* tower = towerFabric.produceTower("BasicTower");
        spawnObject(0,0, tower);


        srand (time(NULL));


        Sprite* newView = new Sprite();
        newView->setRect(0, 0, 100, 100);
        newView->setTexture(Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/Gates.png"));

		gates.setSprite(newView);
        gates.setTag("Gates");
        gates.getDestructibleObject()->setMaximumHealth(5000);
        spawnObject(40,100, &gates);


	}

}

void GameScene::finalizeScene()
{
	Scene::finalizeScene();
}

void GameScene::loadScene()
{
}

void GameScene::unloadScene()
{
}

void GameScene::startUpdate(double timestep)
{
    Scene::startUpdate(timestep);
    if (monsterSpawner.canSpawn(timestep))
	{
        list<SceneObject*> *some = monsterSpawner.doSpawn();

        for(auto ptr = some->begin(); ptr != some->end(); ++ptr)
        {
            int x = rand() % 5 +3;
            int y = rand() % 5 +3;

            spawnObject(x*60,y*70,*ptr);
        }
        delete some;
    }
    if (gates.getDestructibleObject() != nullptr)
    gatesHealthBar.calculateFront(gates.getDestructibleObject()->getCurrentHealth(),gates.getDestructibleObject()->getMaximumHealth());
}

void GameScene::copyToRender() const
{

	list<SceneObject*>::const_iterator  const_iter = sceneObjects.begin();
	list<SceneObject*>::const_iterator end = sceneObjects.end();
	for(;const_iter != end; ++const_iter)
	{
        if (*const_iter == nullptr)
            continue;
		if ( (*const_iter)->getSprite() != nullptr )
		{
            SDL_Rect some =  (*const_iter)->getSprite()->getRect() ;


            Renderer::getInstance()->renderTexture((*const_iter)->getSprite()->getTexture(), &some);

		}
	}


    Scene::copyToRender();
}


