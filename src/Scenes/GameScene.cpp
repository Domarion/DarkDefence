/*
 * GameScene.cpp
 *
 *  Created on: 4 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "GameScene.h"
#include <SDL.h>
#include "../Mob/Tower.h"
#include <cmath>
#include "../GlobalScripts/GameModel.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../Input/InputDispatcher.h"
#include "../GlobalScripts/Renderer.h"




#include "../GlobalConstants.h"

GameScene::GameScene()
:Scene(), Terrain(nullptr), gates(nullptr), waveLabel(), itemAbilitiesStorage(), resPlace(nullptr)
{
	// TODO Auto-generated constructor stub

}

GameScene::~GameScene()
{
    for(size_t i = 0; i != resourceLabels.size(); ++i)
        delete resourceLabels[i];
    resourceLabels.clear();

    if (Terrain != nullptr)
        delete Terrain;
    if (gates != nullptr)
        delete gates;
    //spellStorage.free();


	// TODO Auto-generated destructor stub

  /*  for(int i = 0; i != ResourcesModel::resourceTypeCount; ++i)
    {

      //  delete resourceLabels[i];
    }*/
    //TTF_CloseFont(arialFont);
}

void GameScene::initScene(SceneManager* sceneManagerPtr)
{

	if (!wasInited)
	{

        Scene::initScene(sceneManagerPtr);
        loadData();


        topPanel.setRect(0,0, Renderer::getInstance()->getScreenWidth(), 40);
       // topPanel.loadTexture("GameData/textures/topPanel.png");


        gatesHealthBar.setRect(0, 0, 90, 15);

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



        GameModel::getInstance()->getManaModel()->setLimit(100);

        manaBar.setRect(0, 0, 90, 15);

        SDL_Surface *surface3 = SDL_CreateRGBSurface(0, manaBar.getRect().w, manaBar.getRect().h, 16, 0, 0, 0, 0);
        SDL_Surface *surface4 = SDL_CreateRGBSurface(0, manaBar.getRect().w, manaBar.getRect().h, 16, 0, 0, 0, 0);

        SDL_FillRect(surface3, nullptr, SDL_MapRGB(surface3->format, 50,0, 200));
        SDL_FillRect(surface4, nullptr, SDL_MapRGB(surface4->format, 0,0, 255));

        SDL_Texture  *backTexture1 = Renderer::getInstance()->getTextureFromSurface(surface3);
        SDL_Texture  *frontTexture1 =Renderer::getInstance()->getTextureFromSurface(surface4);
        SDL_FreeSurface(surface3);
        SDL_FreeSurface(surface4);
        manaBar.setTexture(backTexture1);
        manaBar.setFrontTexture(frontTexture1);
        //backTexture1 = nullptr;
        //frontTexture1 = nullptr;
        manaBar.calculateFront(100, 100);
        topPanel.addChild(&manaBar, true);



        resourceLabels.resize(ResourcesModel::resourceTypeCount);
        for(int i = 0; i != ResourcesModel::resourceTypeCount; ++i)
        {
            string s = GameModel::getInstance()->getResourcesModel()->printResourceFromIndex(i);
            resourceLabels[i] = new CompositeLabel();

            resourceLabels[i]->setFont(FontManager::getInstance()->getFontByKind("TextFont"));
            string iconPath = "GameData/textures/Resources/"
                    + GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(i) + ".png";
            resourceLabels[i]->loadIcon( iconPath );
            resourceLabels[i]->setIconRect(0,0, 30 , 30);
            resourceLabels[i]->setPos(0, 0);

           // resourceLabels[i]->setRect(0, 0, 120, 24);
            resourceLabels[i]->setText(s);

            topPanel.addChild(resourceLabels[i]);
        }

        pointsLabel.setFont(FontManager::getInstance()->getFontByKind("TextFont"));
        pointsLabel.setRect(0,0, 30, 20);
        pointsLabel.setPos(0,0);
        topPanel.addChild(&pointsLabel);



        waveLabel.setFont(FontManager::getInstance()->getFontByKind("TextFont"));
        waveLabel.setPos(0,0);
        topPanel.addChild(&waveLabel);

        listGUI.push_back(&topPanel);




        Terrain = objectFabric.produce("Terrain", "none", "GameData/textures/terrain.JPG", Renderer::getInstance()->getScreenWidth() , Renderer::getInstance()->getScreenHeight() );
        spawnObject(0,0, Terrain);
        towerUpgradeController.init(this);
        Tower* tower = towerFabric.produceTower("BasicTower", &towerUpgradeController);
        spawnObject(10, 300, tower);

        resPlace = new ResourcePlace();
        AnimatedSprite* resSprite = new AnimatedSprite();
        resSprite->setRect(0, 0, 200, 200);
        resSprite->loadTexture("GameData/textures/Resources/WheatResource.png");
        resPlace->setSprite(resSprite);
        resPlace->setName("ResourcePlace");
        resPlace->setTag("ResourcePlace");
        spawnObject(300, 200, resPlace);




        srand (time(NULL));


       AnimatedSprite* newView = new AnimatedSprite();
        newView->setRect(0, 0, 100, 100);
        newView->loadTexture("GameData/textures/Gates.png");
        gates = new Gates();
        gates->setSprite(newView);
        gates->setTag("Gates");
        gates->getDestructibleObject()->connectMethod(std::bind(&ProgressBar::calculateFront, &gatesHealthBar, std::placeholders::_1, std::placeholders::_2));
        gates->getDestructibleObject()->setMaximumHealth(5000);


        spawnObject(40,100, gates);

        int x1 = 0;
        int y1 = Renderer::getInstance()->getScreenHeight() - 50;
        int w = 50;
        int h = 50;


        spellStorage.loadWithScene(this);
        std::cout << "productionOfMine beforeItemApply is = " << (GameModel::getInstance()->getMineModelFromListByRes(Enums::ResourceTypes::WOOD)->getProduction()) << std::endl;

        list<string> itemNames = GameModel::getInstance()->getHeroInventory()->getItemNames();
        itemAbilitiesStorage.loadItemAbilities();
        for(auto itemNamePtr = itemNames.begin(); itemNamePtr != itemNames.end(); ++itemNamePtr)
        {
            ItemAbility* temp = itemAbilitiesStorage.getItemAbilityByName(*itemNamePtr);
            if (temp != nullptr)
                temp->init(this);
        }

          std::cout << "productionOfMine AfterItemApplyis = " << (GameModel::getInstance()->getMineModelFromListByRes(Enums::ResourceTypes::WOOD)->getProduction()) << std::endl;

        abilityButtons.resize( GameModel::getInstance()->getAbilityCount());
        for(size_t i = 0; i < abilityButtons.size(); x1 += w, ++i)
        {
           // std::cout << i << std::endl;
            string imgPath = "GameData/textures/Abilities/Ability" + GameModel::getInstance()->getAbilityNameFromIndex(i) + ".png";
            std::cout << imgPath << std::endl;
            abilityButtons[i].setRect( x1, y1, w, h);
            abilityButtons[i].loadTexture(imgPath);
            listGUI.push_back(&abilityButtons[i]);
            if (i < 4)
                abilityButtons[i].ConnectMethod(std::bind(&SpellStorage::setAbilityReady, &spellStorage, GameModel::getInstance()->getAbilityNameFromIndex(i)));
        }


        pauseBtn.setRect(750, 430, 50, 50);
        pauseBtn.loadTexture("GameData/textures/pause-button.png");
        pauseBtn.ConnectMethod(std::bind(&GameScene::sendMessage, this, GlobalConstants::Paused));
        listGUI.push_back(&pauseBtn);

        resumeBtn.setRect(700, 430, 50, 50);
        resumeBtn.loadTexture("GameData/textures/resume-button.png");
        resumeBtn.ConnectMethod(std::bind(&GameScene::sendMessage, this, GlobalConstants::Resumed));
        listGUI.push_back(&resumeBtn);
	}

    for(int i = 0; i < 4; ++i)
        InputDispatcher::getInstance()->addHandler(&abilityButtons[i]);

    InputDispatcher::getInstance()->addHandler(dynamic_cast<InputHandler*>(spellStorage.getAbilityModelWithName("Prick")));
    InputDispatcher::getInstance()->addHandler(resPlace);
    InputDispatcher::getInstance()->addHandler(&pauseBtn);
    InputDispatcher::getInstance()->addHandler(&resumeBtn);
}


void GameScene::startUpdate(double timestep)
{
    Scene::startUpdate(timestep);

    if (gates->getDestructibleObject() != nullptr)
    switch(currentMission.checkStatus())
    {
    case MissionStatuses::mIN_PROGRESS:case MissionStatuses::mNOT_STARTED:
    {
        break;
    }
    case MissionStatuses::mCOMPLETED:
    {
        GameModel::getInstance()->setGameStatus(Enums::GameStatuses::gsWON);
        std::string s1 = "ScoreScene";
        //std::cout << "fuckThemAll" << std::endl;

        GameModel::getInstance()->setMissionReward(currentMission.getReward());
        parentSceneManager->setCurrentSceneByName(s1);
        break;
    }
    case MissionStatuses::mFAILED:
    {
        GameModel::getInstance()->setGameStatus(Enums::GameStatuses::gsLOST);
        std::string s2 = "ScoreScene";
        // std::cout << "idiot" << std::endl;
        parentSceneManager->setCurrentSceneByName(s2);
        break;
    }
    }
    waveLabel.setText(monsterSpawner.getWaveStringInfo());
    if (monsterSpawner.canSpawn(timestep))
	{
        list<SceneObject*> *some = monsterSpawner.doSpawn();

        for(auto ptr = some->begin(); ptr != some->end(); ++ptr)
        {
            int x = rand() % 5 +3;
            int y = rand() % 5 +3;

            spawnObject(x*70,y*50,*ptr);
        }
        delete some;
    }
    else
        if(monsterSpawner.noMoreWaves())
        {
             waveLabel.setText(monsterSpawner.getWaveStringInfo());
            GameModel::getInstance()->setGameStatus(Enums::GameStatuses::gsWON);
            std::string s2 = "ScoreScene";
            parentSceneManager->setCurrentSceneByName(s2);
        }

    pointsLabel.setText(std::to_string(GameModel::getInstance()->getPointsPerWave()));

    GameModel::getInstance()->getManaModel()->regenerate(timestep);
    manaBar.calculateFront(GameModel::getInstance()->getManaModel()->getCurrent(),GameModel::getInstance()->getManaModel()->getLimit());


   // if (gates.getDestructibleObject() != nullptr)
     //   gatesHealthBar.calculateFront(gates.getDestructibleObject()->getCurrentHealth(),gates.getDestructibleObject()->getMaximumHealth());


    if (gates->getDestructibleObject()->getCurrentHealth() <= 0)
        GameModel::getInstance()->setGameStatus(Enums::GameStatuses::gsLOST);

    spellStorage.updateAbilities(timestep);


    for(int i = 0; i != ResourcesModel::resourceTypeCount; ++i)
    {
        string s = GameModel::getInstance()->getResourcesModel()->printResourceFromIndex(i);

        resourceLabels[i]->setText(s);
    }

  //  std::cout << "resfromindex = " << GameModel::getInstance()->getResourcesModel()->printResourceFromIndex(3) <<std::endl;
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
            (*const_iter)->getSprite()->draw();

            //SDL_Rect some =  (*const_iter)->getSprite()->getRect();



            //Renderer::getInstance()->renderTexture((*const_iter)->getSprite()->getTexture(), &some);

		}
	}


    Scene::copyToRender();
}



map<string, AbilityModel *> &GameScene::getAbilityModelList()
{
   return spellStorage.getAbilityModelList();
}

void GameScene::ConnectMethod(std::function<void (string)> handler)
{
    method = handler;
}

AbilityModel *GameScene::getAbilityModelWithName(string name)
{
    return spellStorage.getAbilityModelWithName(name);
}

void GameScene::sendMessage(string msgText)
{
    if (method != nullptr)
        method(msgText);
}

void GameScene::loadData()
{
    int curIndex =  GameModel::getInstance()->getCurrentMissionIndex();

    string s ="GameData/Missions/" + std::to_string(curIndex) +"/Mission.xml";
    GameModel::getInstance()->deserialize(currentMission, s);

    string s00 = "GameData/Missions/" + std::to_string(curIndex) + "/points.txt";
    GameModel::getInstance()->loadMonsterPointsList(s00);


    string s01 = "GameData/MineModels.xml";
    GameModel::getInstance()->loadMinesList(s01);

    GameModel::getInstance()->getResourcesModel()->loadFromFile("GameData/resources.txt");


    GameModel::getInstance()->loadMonsterList("GameData/MonsterList.xml");

    GameModel::getInstance()->loadTowerUpgrades("GameData/TowerTree.xml");
    monsterSpawner.loadWavesInfo("GameData/wavesInfo.txt");

    GameModel::getInstance()->loadAbilitiesNames("GameData/abilities.txt");
}



