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
:Scene()/*, MobFabric()*/, gates(), worldRect(nullptr), mainCamera(nullptr)
{
	// TODO Auto-generated constructor stub

}

GameScene::~GameScene()
{
	// TODO Auto-generated destructor stub
    //delete mainCamera;
    //delete worldRect;

//	delete gates;
    for(int i = 0; i != ResourcesModel::resourceTypeCount; ++i)
    {

        delete resourceLabels[i];
    }

}

void GameScene::initScene(SDL_Renderer* renderer, SceneManager* sceneManagerPtr)
{

	if (!wasInited)
	{
        //worldRect = new SDL_Rect( {0,0, 1920, 1080} );

        //mainCamera = new Camera(300, 300, 800, 600);


		Scene::initScene(renderer, sceneManagerPtr);

        topPanel.setRect(new SDL_Rect({0,0, 800, 40}));
        topPanel.setRenderer(renderer);
        topPanel.loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/topPanel.png");

        GameModel::getInstance()->getResourcesModel()->loadFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/resources.txt");

        gatesHealthBar.setRenderer(renderer);
        gatesHealthBar.setRect(new SDL_Rect({0, 0, 150, 20}));
        SDL_Surface *surface1 = SDL_CreateRGBSurface(0,gatesHealthBar.getRect()->w, gatesHealthBar.getRect()->h, 16, 0, 0, 0, 0);
        //if (surface1 == nullptr)
        //std::cout << "fuck" << std::endl;
        SDL_Surface *surface2 = SDL_CreateRGBSurface(0,gatesHealthBar.getRect()->w, gatesHealthBar.getRect()->h, 16, 0, 0, 0, 0);
        //SDL_Texture *backTexture = SDL_CreateTextureFromSurface(gatesHealthBar.getRenderer(), surface1);
        //SDL_Texture *frontTexture = SDL_CreateTextureFromSurface(gatesHealthBar.getRenderer(), surface2);

        SDL_FillRect(surface1, nullptr, SDL_MapRGB(surface1->format, 150,100, 0));
        SDL_FillRect(surface2, nullptr, SDL_MapRGB(surface2->format, 200,100, 0));

        SDL_Texture  *backTexture = gatesHealthBar.getTextureFromSurface(surface1);
        SDL_Texture  *frontTexture = gatesHealthBar.getTextureFromSurface(surface2);
        SDL_FreeSurface(surface1);
        SDL_FreeSurface(surface2);
        gatesHealthBar.setTexture(backTexture);
        gatesHealthBar.setFrontTexture(frontTexture);
        backTexture = nullptr;
        frontTexture = nullptr;
        gatesHealthBar.calculateFront(100, 100);
        topPanel.addChild(&gatesHealthBar);

        resourceLabels.resize(ResourcesModel::resourceTypeCount);
        for(int i = 0; i != ResourcesModel::resourceTypeCount; ++i)
        {
            string s = GameModel::getInstance()->getResourcesModel()->printResourceFromIndex(i);
            resourceLabels[i] = new Label();
            resourceLabels[i]->setRenderer(renderer);
            resourceLabels[i]->loadFont("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 24);
            resourceLabels[i]->setText(s);
            SDL_Rect* lrect2 = new SDL_Rect({0, 0, 120, 24});
            resourceLabels[i]->setRect(lrect2);

            //listGUI.push_back(resourceLabels[i]);
            topPanel.addChild(resourceLabels[i]);
        }








        listGUI.push_back(&topPanel);



        GameModel::getInstance()->loadMonsterList("/home/kostya_hm/Projects/DarkDefence/GameData/MonsterList.xml");

        GameModel::getInstance()->loadTowerUpgrades("/home/kostya_hm/Projects/DarkDefence/GameData/TowerTree.xml");
        monsterSpawner.loadWavesInfo("/home/kostya_hm/Projects/DarkDefence/GameData/wavesInfo.txt");


        Terrain = objectFabric.produce("Terrain", "none", renderer, "/home/kostya_hm/Projects/DarkDefence/GameData/textures/terrain.JPG", 800, 600);
        Scene::spawnObject(0,0, Terrain);

        Mob* tower = towerFabric.produceTower("BasicTower", renderer);
        Scene::spawnObject(0,0, tower);


        srand (time(NULL));


     /*   SDL_Rect first = {200,200, 300, 300};
        SDL_Rect second = {300, 300, 800, 600};
        SDL_Rect resultRect;
        SDL_IntersectRect(&first, &second, &resultRect);*/

        //std::cout << resultRect.x << '\t' << resultRect.y << '\t' << resultRect.w << '\t' << resultRect.h << std::endl;

		Sprite* newView = new Sprite();
        newView->setRect(new SDL_Rect({40, 100, 100, 100}));
		newView->setRenderer(renderer);
        newView->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/Gates.png");
		gates.setSprite(newView);
        gates.setTag("Gates");
        gates.getDestructibleObject()->setMaximumHealth(1000);

		sceneObjects.push_back(&gates);





      //  std::cout << resultRect.x << '\t' << resultRect.y << '\t' << resultRect.w << '\t' << resultRect.h << std::endl;
		//string aName, string aTag, int aMaxHealth, double aProtection[]
	/*	int prot[] = {10, 0 ,0 ,0};
		gates = new DestructibleObject("Gates", "Gates", 100, prot);
		gates->getSprite()->setRect(temp);
		gates->getSprite()->setRenderer(renderer);
		gates->getSprite()->loadTextureFromFile("/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/textures/terrain.JPG");*/
		//GameModel::getInstance()->loadTowerUpgrades("/home/kostya_hm/workspace/DarkDefenceCppPort/GameData/Towers.xml");
		//::cout << GameModel::getInstance()->getRootTower()->getData().getName() << std::endl;
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
        list<SceneObject*> *some = monsterSpawner.doSpawn(rendererptr);
        //sceneObjects.insert(sceneObjects.end(), some.begin(), some.end());
        for(auto ptr = some->begin(); ptr != some->end(); ++ptr)
        {
            int x = rand() % 5 +3;
            int y = rand() % 5 +3;

            Scene::spawnObject(x*60,y*70,*ptr);
        }
        delete some;
    }
    if (gates.getDestructibleObject() != nullptr)
    gatesHealthBar.calculateFront(gates.getDestructibleObject()->getCurrentHealth(),gates.getDestructibleObject()->getMaximumHealth());
}

void GameScene::copyToRender(SDL_Renderer* renderer) const
{
    //SDL_Rect cameraRect = mainCamera->getRect();
	list<SceneObject*>::const_iterator  const_iter = sceneObjects.begin();
	list<SceneObject*>::const_iterator end = sceneObjects.end();
	for(;const_iter != end; ++const_iter)
	{
        if (*const_iter == nullptr)
            continue;
		if ( (*const_iter)->getSprite() != nullptr )
		{
            if ((*const_iter)->getSprite()->getRect() == nullptr)
                continue;
			SDL_Rect some = *( (*const_iter)->getSprite()->getRect() );

          //  SDL_Rect resultRect = mainCamera->cameraCulling(&some);
          //  SDL_Rect some2 = mainCamera->cameraCulling(&some);

            //some.x = 0;
          // some.y = 0;


           // SDL_QueryTexture((*const_iter)->getSprite()->getTexture(), nullptr, nullptr, &resultRect.w, &resultRect.h);
            SDL_RenderCopy(renderer, (*const_iter)->getSprite()->getTexture(), nullptr, &some);
		}
	}


	Scene::copyToRender(renderer);
}


