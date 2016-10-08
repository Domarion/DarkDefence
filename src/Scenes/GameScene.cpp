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
#include "../Utility/textfilefunctions.h"



#include "../GlobalConstants.h"


GameScene::GameScene(std::shared_ptr<RenderingSystem> &aRenderer)
:Scene(aRenderer)
, gates(nullptr)
, gatesHealthBar(nullptr)
, manaBar(nullptr)
, pointsLabel(nullptr)
, waveLabel(nullptr)
, itemAbilitiesStorage()
, tileMap(nullptr)
{
    srand (time(NULL));
}

GameScene::~GameScene()
{

    delete tileMap;
}

void GameScene::init(SceneManager* sceneManagerPtr)
{
    Scene::init(sceneManagerPtr);
    loadData();

    initUILayer();
    placeSceneObjects();
    applyArtefactEffects();

}


void GameScene::startUpdate(double timestep)
{
    Scene::startUpdate(timestep);

    if (gates != nullptr && gates->getDestructibleObject() != nullptr)
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
        getParentSceneManager()->setCurrentSceneByName(s1);
        break;
    }
    case MissionStatuses::mFAILED:
    {
        GameModel::getInstance()->setGameStatus(Enums::GameStatuses::gsLOST);
        std::string s2 = "ScoreScene";
        // std::cout << "idiot" << std::endl;
        getParentSceneManager()->setCurrentSceneByName(s2);
        break;
    }
    }
    waveLabel->setText(monsterSpawner.getWaveStringInfo());
    if (monsterSpawner.canSpawn(timestep))
	{
        if (tileMap == nullptr)
        {
            std::cout << "TileIsNullinGameScene" << std::endl;
        }

        list<Mob*> *some = monsterSpawner.doSpawn(tileMap);

        for(auto ptr = some->begin(); ptr != some->end(); ++ptr)
        {
            int x = rand() % 5 +3;
            int y = rand() % 5 +3;
            if ((*ptr)->getTileMapManager() == nullptr)
            {
                std::cout << "ptr->getTileMapManager = nullptr1" << std::endl;
            }
            spawnObject(x*70,y*50,*ptr);
            if ((*ptr)->getTileMapManager() == nullptr)
            {
                std::cout << "afterspqn->getTileMapManager = nullptr1" << std::endl;
            }


        }
        delete some;
    }
    else
        if(monsterSpawner.noMoreWaves())
        {
             waveLabel->setText(monsterSpawner.getWaveStringInfo());
            GameModel::getInstance()->setGameStatus(Enums::GameStatuses::gsWON);
            GameModel::getInstance()->setMissionReward(currentMission.getReward());
            std::string s2 = "ScoreScene";
            getParentSceneManager()->setCurrentSceneByName(s2);
        }

    if (pointsLabel != nullptr)
        pointsLabel->setText(std::to_string(GameModel::getInstance()->getPointsPerWave()));

    GameModel::getInstance()->getManaModel()->regenerate(timestep);

    if (manaBar != nullptr)
        manaBar->calculateFront(GameModel::getInstance()->getManaModel()->getCurrent(),GameModel::getInstance()->getManaModel()->getLimit());


    if (gates != nullptr && gates->getDestructibleObject()->getCurrentHealth() <= 0)
        GameModel::getInstance()->setGameStatus(Enums::GameStatuses::gsLOST);

    spellStorage.updateAbilities(timestep);


    for(int i = 0; i != ResourcesModel::resourceTypeCount; ++i)
    {
        string s = GameModel::getInstance()->getResourcesModel()->printResourceFromIndex(i);
        if (resourceLabels[i] != nullptr)
            resourceLabels[i]->setText(s);
    }

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

    string tileMapMatrixPath = "GameData/Missions/" + std::to_string(curIndex) + "/map.txt";
    vector<vector<int> > aMapTemplate = androidText::loadMatrixFromFile(tileMapMatrixPath);
    tileMap = new TileMapManager(aMapTemplate);
}

void GameScene::initTopPanel()
{
    GroupBox* topPanel = new GroupBox();
    topPanel->setRect(0,0, Renderer::getInstance()->getScreenWidth(), 40);
   // topPanel.loadTexture("GameData/textures/topPanel.png");

    gatesHealthBar = new ProgressBar();

    gatesHealthBar->setRect(0, 0, 90, 15);

    SDL_Surface *surface1 = SDL_CreateRGBSurface(0, gatesHealthBar->getRect().w, gatesHealthBar->getRect().h, 16, 0, 0, 0, 0);
    SDL_Surface *surface2 = SDL_CreateRGBSurface(0, gatesHealthBar->getRect().w, gatesHealthBar->getRect().h, 16, 0, 0, 0, 0);

    SDL_FillRect(surface1, nullptr, SDL_MapRGB(surface1->format, 150,100, 0));
    SDL_FillRect(surface2, nullptr, SDL_MapRGB(surface2->format, 200,100, 0));



    SDL_Texture  *backTexture = Renderer::getInstance()->getTextureFromSurface(surface1);
    SDL_Texture  *frontTexture = Renderer::getInstance()->getTextureFromSurface(surface2);
    SDL_FreeSurface(surface1);
    SDL_FreeSurface(surface2);
    gatesHealthBar->setTexture(backTexture);
    gatesHealthBar->setFrontTexture(frontTexture);

    gatesHealthBar->calculateFront(5000, 5000);
    topPanel->addChild(gatesHealthBar);


    manaBar = new ProgressBar();
    GameModel::getInstance()->getManaModel()->setLimit(100);

    manaBar->setRect(0, 0, 90, 15);

    SDL_Surface *surface3 = SDL_CreateRGBSurface(0, manaBar->getRect().w, manaBar->getRect().h, 16, 0, 0, 0, 0);
    SDL_Surface *surface4 = SDL_CreateRGBSurface(0, manaBar->getRect().w, manaBar->getRect().h, 16, 0, 0, 0, 0);

    SDL_FillRect(surface3, nullptr, SDL_MapRGB(surface3->format, 50,0, 200));
    SDL_FillRect(surface4, nullptr, SDL_MapRGB(surface4->format, 0,0, 255));

    SDL_Texture  *backTexture1 = Renderer::getInstance()->getTextureFromSurface(surface3);
    SDL_Texture  *frontTexture1 = Renderer::getInstance()->getTextureFromSurface(surface4);
    SDL_FreeSurface(surface3);
    SDL_FreeSurface(surface4);
    manaBar->setTexture(backTexture1);
    manaBar->setFrontTexture(frontTexture1);
    manaBar->calculateFront(100, 100);
    topPanel->addChild(manaBar, true);



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

        topPanel->addChild(resourceLabels[i]);
    }
    pointsLabel = new Label();
    pointsLabel->setFont(FontManager::getInstance()->getFontByKind("TextFont"));
    pointsLabel->setRect(0,0, 30, 20);
    pointsLabel->setPos(0,0);
    topPanel->addChild(pointsLabel);


    waveLabel = new Label();
    waveLabel->setFont(FontManager::getInstance()->getFontByKind("TextFont"));
    waveLabel->setPos(0,0);
    topPanel->addChild(waveLabel);

    //Scene::addToUIList(topPanel);
}

void GameScene::initAbilitiesButtons()
{
    int x1 = 0;
    int y1 = Renderer::getInstance()->getScreenHeight() - 50;
    int w = 50;
    int h = 50;

    spellStorage.loadWithScene(this);


    vector<ImageButton*> abilityButtons( GameModel::getInstance()->getAbilityCount());

    for(size_t i = 0; i < abilityButtons.size(); x1 += w, ++i)
    {
        abilityButtons[i] = new ImageButton();
        abilityButtons[i]->setRect( x1, y1, w, h);

        string imgPath = "GameData/textures/Abilities/Ability" + GameModel::getInstance()->getAbilityNameFromIndex(i) + ".png";
        abilityButtons[i]->loadTexture(imgPath);
        //Scene::addToUIList(abilityButtons[i]);

        abilityButtons[i]->ConnectMethod(std::bind(&SpellStorage::setAbilityReady, &spellStorage, GameModel::getInstance()->getAbilityNameFromIndex(i)));
    }
    InputHandler* prickhandler = dynamic_cast<InputHandler*>(spellStorage.getAbilityModelWithName("Prick"));
    if(prickhandler != nullptr)
    {
        InputDispatcher::getInstance()->addHandler(prickhandler);
    }
    else
        std::cout << "WTF_prick" << std::endl;
}

void GameScene::initUILayer()
{
    initTopPanel();
    initAbilitiesButtons();

    ImageButton* pauseBtn = new ImageButton();
    pauseBtn->setRect(750, 430, 50, 50);
    pauseBtn->loadTexture("GameData/textures/pause-button.png");
    pauseBtn->ConnectMethod(std::bind(&GameScene::sendMessage, this, GlobalConstants::Paused));
    //Scene::addToUIList(pauseBtn);

    ImageButton* resumeBtn = new ImageButton();
    resumeBtn->setRect(700, 430, 50, 50);
    resumeBtn->loadTexture("GameData/textures/resume-button.png");
    resumeBtn->ConnectMethod(std::bind(&GameScene::sendMessage, this, GlobalConstants::Resumed));
    //Scene::addToUIList(resumeBtn);
}

void GameScene::placeResourcesPlaces()
{


    ResourcePlace *resPlace = new ResourcePlace(1000, Enums::ResourceTypes::WOOD);
    AnimatedSprite* resSprite = new AnimatedSprite();
    resSprite->setRect(0, 0, 200, 200);

    string resourceName = GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(static_cast<int> (resPlace->getResourceType()));
    string texturePath = "GameData/textures/Resources/" + resourceName + "Resource.png";
    resSprite->loadTexture(texturePath);
    resPlace->setSprite(resSprite);
    resPlace->setName("ResourcePlace");
    resPlace->setTag("ResourcePlace");
    spawnObject(400, 100, resPlace);
}

void GameScene::placeCastle()
{
    AnimatedSprite* newView = new AnimatedSprite();
     newView->setRect(0, 0, 120, 120);
     newView->loadTexture("GameData/textures/Castle2.png");
     gates = new Gates();
     gates->setSprite(newView);
     gates->setTag("Gates");
     gates->getDestructibleObject()->connectMethod(std::bind(&ProgressBar::calculateFront, gatesHealthBar, std::placeholders::_1, std::placeholders::_2));
     gates->getDestructibleObject()->setMaximumHealth(5000);
     spawnObject(40,100, gates);
}

void GameScene::placeTowers()
{
    towerUpgradeController.init(this);

    list<string> towerNames = {"WatcherTower","BallistaTower", "CatapultTower", "MageTower", "ProductivityTower",
                               "WindTower", "EarthTower","CloudTower"};
    int x = 10;
    for(const auto& towerName : towerNames)
    {
        Tower* tower = towerFabric.produceTower(towerName, &towerUpgradeController, tileMap);
        spawnObject(x, 300, tower);
        x+= 60;
    }

}

void GameScene::placeSceneObjects()
{
    SceneObject* Terrain = objectFabric.produce("Terrain", "none", "GameData/textures/terrain.JPG", Renderer::getInstance()->getScreenWidth() , Renderer::getInstance()->getScreenHeight() );
    spawnObject(0,0, Terrain);

    placeResourcesPlaces();
    placeTowers();
    placeCastle();
}

void GameScene::applyArtefactEffects()
{

    std::cout << "productionOfMine beforeItemApply is = " << (GameModel::getInstance()->getMineModelFromListByRes(Enums::ResourceTypes::WOOD)->getProduction()) << std::endl;

    vector<string> itemNames = GameModel::getInstance()->getHeroInventory()->getItemNames();
    itemAbilitiesStorage.loadItemAbilities();
    for(auto itemNamePtr = itemNames.begin(); itemNamePtr != itemNames.end(); ++itemNamePtr)
    {
        ItemAbility* temp = itemAbilitiesStorage.getItemAbilityByName(*itemNamePtr);
        if (temp != nullptr)
            temp->init(this);
    }

      std::cout << "productionOfMine AfterItemApplyis = " << (GameModel::getInstance()->getMineModelFromListByRes(Enums::ResourceTypes::WOOD)->getProduction()) << std::endl;
}



void GameScene::clear()
{
    pointsLabel = nullptr;
    waveLabel = nullptr;
    manaBar = nullptr;
    gatesHealthBar = nullptr;
    gates = nullptr;
    for(auto &resourcelabel : resourceLabels)
        resourcelabel = nullptr;
    currentMission.reset();
    monsterSpawner.reset();
    Scene::clear();
}


