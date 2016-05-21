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

GameScene::GameScene()
:Scene(), gates(), arialFont(nullptr), waveLabel()
{
	// TODO Auto-generated constructor stub

}

GameScene::~GameScene()
{
	// TODO Auto-generated destructor stub

    for(int i = 0; i != ResourcesModel::resourceTypeCount; ++i)
    {

      //  delete resourceLabels[i];
    }
    //TTF_CloseFont(arialFont);
}

void GameScene::initScene(SceneManager* sceneManagerPtr)
{

	if (!wasInited)
	{

        Scene::initScene(sceneManagerPtr);
       // GameModel::getInstance()->loadMobAbilities();


        int curIndex =  GameModel::getInstance()->getCurrentMissionIndex();

        string s ="/home/kostya_hm/Projects/DarkDefence/GameData/Missions/" + std::to_string(curIndex) +"/Mission.xml";
        GameModel::getInstance()->deserialize(currentMission, s);

        string s00 = "/home/kostya_hm/Projects/DarkDefence/GameData/Missions/" + std::to_string(curIndex) + "/points.txt";
        GameModel::getInstance()->loadMonsterPointsList(s00);


        string s01 = "/home/kostya_hm/Projects/DarkDefence/GameData/MineModels.xml";
        GameModel::getInstance()->loadMinesList(s01);

        topPanel.setRect(0,0, 800, 40);
       // topPanel.setTexture(Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/topPanel.png"));


       // GameModel::getInstance()->getResourcesModel()->loadFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/resources.txt");


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
        SDL_Texture  *frontTexture1 = Renderer::getInstance()->getTextureFromSurface(surface4);
        SDL_FreeSurface(surface3);
        SDL_FreeSurface(surface4);
        manaBar.setTexture(backTexture1);
        manaBar.setFrontTexture(frontTexture1);
        //backTexture1 = nullptr;
        //frontTexture1 = nullptr;
        manaBar.calculateFront(100, 100);
        topPanel.addChild(&manaBar, true);




        arialFont = Renderer::getInstance()->loadFontFromFile("/home/kostya_hm/Projects/DarkDefence/Fonts/arial.ttf", 20);
        SDL_Color arialFontColor = {255, 255, 255};




        resourceLabels.resize(ResourcesModel::resourceTypeCount);
        for(int i = 0; i != ResourcesModel::resourceTypeCount; ++i)
        {
            string s = GameModel::getInstance()->getResourcesModel()->printResourceFromIndex(i);
            resourceLabels[i] = new CompositeLabel();

            resourceLabels[i]->setFont(arialFont, arialFontColor);
            string iconPath = "/home/kostya_hm/Projects/DarkDefence/GameData/textures/Resources/"
                    + GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(i) + ".png";
            resourceLabels[i]->setIcon(Renderer::getInstance()->loadTextureFromFile( iconPath ));
            resourceLabels[i]->setIconRect(0,0, 30 , 30);
            resourceLabels[i]->setPos(0, 0);

           // resourceLabels[i]->setRect(0, 0, 120, 24);
            resourceLabels[i]->setText(s);

            topPanel.addChild(resourceLabels[i]);
        }

        pointsLabel.setFont(arialFont, arialFontColor);
        pointsLabel.setRect(0,0, 30, 20);
        pointsLabel.setPos(0,0);
        topPanel.addChild(&pointsLabel);



        waveLabel.setFont(arialFont, arialFontColor);
        waveLabel.setPos(0,0);
        topPanel.addChild(&waveLabel);

        listGUI.push_back(&topPanel);


        GameModel::getInstance()->loadMonsterList("/home/kostya_hm/Projects/DarkDefence/GameData/MonsterList.xml");

        GameModel::getInstance()->loadTowerUpgrades("/home/kostya_hm/Projects/DarkDefence/GameData/TowerTree.xml");
        monsterSpawner.loadWavesInfo("/home/kostya_hm/Projects/DarkDefence/GameData/wavesInfo.txt");


        Terrain = objectFabric.produce("Terrain", "none", "/home/kostya_hm/Projects/DarkDefence/GameData/textures/terrain.JPG", 800, 600);
        spawnObject(0,0, Terrain);
        towerUpgradeController.init(this);
        Tower* tower = towerFabric.produceTower("BasicTower", &towerUpgradeController);
        spawnObject(0, 400, tower);

        resPlace = new ResourcePlace();
       Sprite* resSprite = new Sprite();
        resSprite->setRect(0, 0, 200, 200);
        resSprite->setTexture(Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/Resources/WheatResource.png"));
        resPlace->setSprite(resSprite);
        resPlace->setName("ResourcePlace");
        resPlace->setTag("ResourcePlace");
        spawnObject(300, 200, resPlace);




        srand (time(NULL));


       Sprite* newView = new Sprite();
        newView->setRect(0, 0, 100, 100);
        newView->setTexture(Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/Gates.png"));

		gates.setSprite(newView);
        gates.setTag("Gates");
        gates.getDestructibleObject()->setMaximumHealth(5000);
        spawnObject(40,100, &gates);

        int x1 = 0;
        int y1 = Renderer::getInstance()->getScreenHeight() - 50;
        int w = 50;
        int h = 50;
        GameModel::getInstance()->loadAbilitiesNames("/home/kostya_hm/Projects/DarkDefence/GameData/abilities.txt");

        AbilityMagicStones* magicStones = new AbilityMagicStones();

        magicStones->init(this);
        magicStones->setManaCost(100);
        magicStones->setCooldownTime(10000);
        magicStones->setWorkTime(10000);


        AbilitySnowStorm* snowStorm = new AbilitySnowStorm();
        snowStorm->init(this);
        snowStorm->setManaCost(100);
        snowStorm->setCooldownTime(10000);
        snowStorm->setWorkTime(10000);
        snowStorm->setDamagePerSecond(30);


        AbilityShrink* shrink = new AbilityShrink();
        shrink->init(this);
        shrink->setManaCost(100);
        shrink->setCooldownTime(20000);
        shrink->setWorkTime(11000);
        shrink->setDamagePerSecond(0.2);

        AbilityPrick* prick = new AbilityPrick();
        prick->init(this);
        prick->setManaCost(100);
        prick->setCooldownTime(10000);
        prick->setWorkTime(0);
        prick->setDamage(120);

        abilityModelsMap["MagicStones"] = magicStones;
        abilityModelsMap["SnowStorm"] = snowStorm;
        abilityModelsMap["Shrink"] = shrink;
        abilityModelsMap["Prick"] = prick;
        std::cout << "productionOfMine beforeItemApply is = " << (GameModel::getInstance()->getMineModelFromListByRes(Enums::ResourceTypes::WOOD)->getProduction()) << std::endl;

        list<string> itemNames = GameModel::getInstance()->getHeroInventory()->getItemNames();
        GameModel::getInstance()->loadItemAbilities();
        for(auto itemNamePtr = itemNames.begin(); itemNamePtr != itemNames.end(); ++itemNamePtr)
        {
            ItemAbility* temp = GameModel::getInstance()->getItemAbilityByName(*itemNamePtr);
            if (temp != nullptr)
                temp->init(this);


        }

          std::cout << "productionOfMine AfterItemApplyis = " << (GameModel::getInstance()->getMineModelFromListByRes(Enums::ResourceTypes::WOOD)->getProduction()) << std::endl;

        abilityButtons.resize( GameModel::getInstance()->getAbilityCount());
        for(int i = 0; i < abilityButtons.size(); x1 += w, ++i)
        {
           // std::cout << i << std::endl;
            string imgPath = "/home/kostya_hm/Projects/DarkDefence/GameData/textures/Abilities/Ability" + GameModel::getInstance()->getAbilityNameFromIndex(i) + ".png";
            std::cout << imgPath << std::endl;
            abilityButtons[i].setRect( x1, y1, w, h);
            abilityButtons[i].setTexture(Renderer::getInstance()->loadTextureFromFile(imgPath));
            listGUI.push_back(&abilityButtons[i]);
            if (i < 4)
                abilityButtons[i].ConnectMethod(std::bind(&GameScene::setActiveMstones, this, GameModel::getInstance()->getAbilityNameFromIndex(i)));
        }




	}

    for(int i = 0; i < 4; ++i)
        InputDispatcher::getInstance()->addHandler(&abilityButtons[i]);

    InputDispatcher::getInstance()->addHandler(dynamic_cast<InputHandler*>(abilityModelsMap["Prick"]));
    InputDispatcher::getInstance()->addHandler(resPlace);
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

    if (gates.getDestructibleObject() != nullptr)
    switch(currentMission.checkStatus())
    {
    case MissionStatuses::mIN_PROGRESS:
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

            spawnObject(x*60,y*70,*ptr);
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


    if (gates.getDestructibleObject() != nullptr)
        gatesHealthBar.calculateFront(gates.getDestructibleObject()->getCurrentHealth(),gates.getDestructibleObject()->getMaximumHealth());


    if (gates.getDestructibleObject()->getCurrentHealth() <= 0)
        GameModel::getInstance()->setGameStatus(Enums::GameStatuses::gsLOST);


    for(auto ptr0 = abilityModelsMap.begin(); ptr0 != abilityModelsMap.end(); ++ptr0)
        ptr0->second->update(timestep);

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

AbilityModel * const GameScene::getAbilityModelWithName(string name)
{
    return abilityModelsMap[name];
}

map<std::__cxx11::string, AbilityModel *> &GameScene::getAbilityModelList()
{
    return abilityModelsMap;
}

/*void GameScene::receiveTowerUpgrade(Tower *tower, int x, int y)
{

    //currentGrade.
}*/

void GameScene::setActiveMstones(string s)
{

    abilityModelsMap[s]->setAsReady();
}


