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
#include "../Utility/textfilefunctions.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImageButton.h"


#include "../GlobalConstants.h"


GameScene::GameScene(std::shared_ptr<RenderingSystem> &aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher)
: Scene(aRenderer, aInputDispatcher)
, gates(nullptr)
, gatesHealthBar(nullptr)
, manaBar(nullptr)
, pointsLabel(nullptr)
, waveLabel(nullptr)
, monsterSpawner(aRenderer)
, itemAbilitiesStorage()
, towerUpgradeController(std::make_shared<TowerUpgradeController>())
, tileMap(nullptr)
, mManaModel(nullptr)

{
    srand (static_cast<unsigned int>(time(NULL)));
}

GameScene::~GameScene()
{
}

void GameScene::init(std::shared_ptr<SceneManager> sceneManagerPtr)
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
    switch(currentMission.checkStatus(GameModel::getInstance()->getGameStatus()))
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

    if (waveLabel != nullptr)
    {
    waveLabel->setText(monsterSpawner.getWaveStringInfo());
    if (monsterSpawner.canSpawn(timestep))
	{
        if (tileMap == nullptr)
        {
            std::cout << "TileIsNullinGameScene" << std::endl;
        }

        auto some = monsterSpawner.doSpawn(tileMap);

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
    }
    if (pointsLabel != nullptr)
        pointsLabel->setText(std::to_string(GameModel::getInstance()->getPointsPerWave()));

    if (mManaModel != nullptr)
    {
        mManaModel->regenerate(timestep);

        if (manaBar != nullptr)
            manaBar->calculateProgress(mManaModel->getCurrent(), mManaModel->getLimit());
    }


    if (gates != nullptr && gates->getDestructibleObject()->getCurrentHealth() <= 0)
        GameModel::getInstance()->setGameStatus(Enums::GameStatuses::gsLOST);

    spellStorage.updateAbilities(timestep);


    for(size_t i = 0; i != GlobalConstants::resourceTypeCount; ++i)
    {
        string s = GameModel::getInstance()->getResourcesModel()->printResourceFromIndex(i);
        if (resourceLabels[i] != nullptr)
            resourceLabels[i]->setText(s);
    }

}


map<string, std::shared_ptr<AbilityModel>> &GameScene::getAbilityModelList()
{
   return spellStorage.getAbilityModelList();
}

void GameScene::ConnectMethod(std::function<void (string)> handler)
{
    method = handler;
}

std::shared_ptr<AbilityModel> GameScene::getAbilityModelWithName(string name)
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

//    GameModel::getInstance()->getResourcesModel()->loadFromFile("GameData/resources.txt");


    GameModel::getInstance()->loadMonsterList("GameData/MonsterList.xml");

    GameModel::getInstance()->loadTowerUpgrades("GameData/TowerTree.xml");
    monsterSpawner.loadWavesInfo("GameData/wavesInfo.txt");

    GameModel::getInstance()->loadAbilitiesNames("GameData/abilities.txt");

    string tileMapMatrixPath = "GameData/Missions/" + std::to_string(curIndex) + "/map.txt";
    vector<vector<int> > aMapTemplate = androidText::loadMatrixFromFile(tileMapMatrixPath);
    tileMap = std::make_shared<TileMapManager>(aMapTemplate);
}

void GameScene::initResourceView()
{
    auto resourcePanel = std::make_shared<ConcreteComposite>(renderer);
    resourcePanel->setSize(Size(MainRect->getSize().width/3, 50));
    resourcePanel->setPosition(MainRect->getNextPosition());

    Font labelFont = FontManager::getInstance()->getFontByKind2("TextFont");
    resourceLabels.resize(GlobalConstants::resourceTypeCount);
    for(size_t i = 0; i != GlobalConstants::resourceTypeCount; ++i)
    {
        string iconPath = "GameData/textures/Resources/"
                + GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(i) + ".png";

        auto resourceIcon = std::make_shared<UIImage>(renderer);
        resourceIcon->loadTexture(iconPath);
        resourceIcon->setSize(Size(48, 48));
        resourceIcon->setPosition(resourcePanel->getNextPosition());
        resourcePanel->addChild(resourceIcon);

        string labelText = GameModel::getInstance()->getResourcesModel()->printResourceFromIndex(i);
        resourceLabels[i] = std::make_shared<UILabel>(labelText, labelFont, renderer);
        resourceLabels[i]->setSize(Size(30, 25));
        resourceLabels[i]->setPosition(resourcePanel->getNextPosition());

        resourcePanel->addChild(resourceLabels[i]);
    }
    MainRect->addChild(resourcePanel);

}

void GameScene::initProgressBars()
{

    auto progressBarGroup = std::make_shared<ConcreteComposite>(renderer);
    progressBarGroup->setSize(Size(100, 50));
    progressBarGroup->setPosition(MainRect->getNextPosition());

    Texture2D gatesHealthBarBack(renderer);
    gatesHealthBarBack.loadTexture("GameData/textures/HealthBarEmpty.png");
    Texture2D gatesHealthBarFront(renderer);
    gatesHealthBarFront.loadTexture("GameData/textures/HealthBarFull.png");

    gatesHealthBar = std::make_shared<UIProgressBar>(renderer, gatesHealthBarBack, gatesHealthBarFront);
    gatesHealthBar->setSize(Size(progressBarGroup->getSize().width, progressBarGroup->getSize().height/2));
    gatesHealthBar->calculateProgress(5000, 5000);
    progressBarGroup->addChild(gatesHealthBar);

    Texture2D manaBarBack(renderer);
    manaBarBack.loadTexture("GameData/textures/ManaBarEmpty.png");
    Texture2D manaBarFront(renderer);
    manaBarFront.loadTexture("GameData/textures/ManaBarFull.png");

    manaBar = std::make_shared<UIProgressBar>(renderer, manaBarBack, manaBarFront);
    manaBar->setSize(Size(progressBarGroup->getSize().width, progressBarGroup->getSize().height/2));
    manaBar->setPosition(progressBarGroup->getNextVerticalPosition());
    manaBar->calculateProgress(100, 100);
    progressBarGroup->addChild(manaBar);

    MainRect->addChild(progressBarGroup);
}

void GameScene::initTopPanel()
{
    initProgressBars();
    initResourceView();

    auto miniGroup = std::make_shared<ConcreteComposite>(renderer);
    miniGroup->setSize(Size(MainRect->getSize().width/4, 50));
    miniGroup->setPosition(MainRect->getNextPosition());

    Font aFont = FontManager::getInstance()->getFontByKind2("TextFont");
    pointsLabel = std::make_shared<UILabel>("none", aFont, renderer);
    pointsLabel->setSize(Size(50, 50));

    miniGroup->addChild(pointsLabel);

    waveLabel = std::make_shared<UILabel>("none", aFont, renderer);
    waveLabel->setSize(Size(100, 50));
    waveLabel->setPosition(miniGroup->getNextPosition());
    miniGroup->addChild(waveLabel);

    MainRect->addChild(miniGroup);
}

void GameScene::initAbilitiesButtons()
{

    mManaModel = std::make_shared<ManaGlobal>();

    Position abilityButtonPos(0, MainRect->getSize().height - 48);
    Size abilityButtonSize(48, 48);


    spellStorage.loadWithScene(shared_from_this(), mManaModel);

    auto abilityButtonsGroup = std::make_shared<ConcreteComposite>(renderer);
    abilityButtonsGroup->setSize(Size(MainRect->getSize().width/3, abilityButtonSize.height));
    abilityButtonsGroup->setPosition(abilityButtonPos);


    size_t abilityButtonCount = GameModel::getInstance()->getAbilityCount();

    for(size_t i = 0; i < abilityButtonCount; ++i)
    {
        auto abilityButton = std::make_shared<UIImageButton>(renderer);
        string imgPath = "GameData/textures/Abilities/Ability" + GameModel::getInstance()->getAbilityNameFromIndex(i) + ".png";

        abilityButton->loadTexture(imgPath);
        abilityButton->setSize(abilityButtonSize);
        abilityButton->setPosition(abilityButtonsGroup->getNextPosition());
        abilityButton->ConnectMethod(std::bind(&SpellStorage::setAbilityReady, &spellStorage, GameModel::getInstance()->getAbilityNameFromIndex(i)));
        abilityButtonsGroup->addChild(abilityButton);

    }
    MainRect->addChild(abilityButtonsGroup);

    auto prickhandler = std::dynamic_pointer_cast<InputHandler>(spellStorage.getAbilityModelWithName("Prick"));
    if(prickhandler != nullptr)
    {
        mInputDispatcher->addHandler(prickhandler);
    }
    else
        std::cout << "WTF_prick" << std::endl;
}

void GameScene::initUILayer()
{
    initTopPanel();



    Size buttonSize(48, 48);
    auto pauseButton = std::make_shared<UIImageButton>(renderer);
    pauseButton->loadTexture("GameData/textures/pause-button.png");
    pauseButton->setSize(buttonSize);
    pauseButton->setPosition(MainRect->getNextPosition());
    pauseButton->ConnectMethod(std::bind(&GameScene::sendMessage, this, GlobalConstants::Paused));
    MainRect->addChild(pauseButton);

    auto resumeButton = std::make_shared<UIImageButton>(renderer);
    resumeButton->loadTexture("GameData/textures/resume-button.png");
    resumeButton->setSize(buttonSize);
    resumeButton->setPosition(MainRect->getNextPosition());
    resumeButton->ConnectMethod(std::bind(&GameScene::sendMessage, this, GlobalConstants::Resumed));
    MainRect->addChild(resumeButton);

    Scene::addToUIList(MainRect);

    initAbilitiesButtons();
}

void GameScene::placeResourcesPlaces()
{


    auto resPlace = std::make_shared<ResourcePlace>(700, Enums::ResourceTypes::WOOD);
    auto resSprite = std::make_shared<AnimationSceneSprite>(renderer);

    resSprite->setSize(Size(200, 200));

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
    auto newView = std::make_shared<AnimationSceneSprite>(renderer);


     newView->setSize(Size(120, 120));
     newView->loadTexture("GameData/textures/Castle2.png");
     gates = std::make_shared<Gates>();
     gates->setSprite(newView);
     gates->setTag("Gates");
     gates->getDestructibleObject()->connectMethod(std::bind(&UIProgressBar::calculateProgress, gatesHealthBar, std::placeholders::_1, std::placeholders::_2));
     gates->getDestructibleObject()->setMaximumHealth(5000);
     spawnObject(40,100, gates);
}

void GameScene::placeTowers()
{
    towerUpgradeController->init(shared_from_this(), renderer);

    list<string> towerNames = {"WatcherTower","BallistaTower", "CatapultTower", "MageTower", "ProductivityTower",
                               "WindTower", "EarthTower","CloudTower"};
    int x = 10;
    for(const auto& towerName : towerNames)
    {
        std::shared_ptr<Tower> tower= towerFabric.produceTower(towerName, renderer, towerUpgradeController, tileMap);
        spawnObject(x, 300, tower);
        x+= 60;
    }

}

void GameScene::placeSceneObjects()
{
    std::shared_ptr<SceneObject> Terrain = objectFabric.produce("Terrain", "none", "GameData/textures/terrain.png", 0 , 0, renderer );
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
        auto temp = itemAbilitiesStorage.getItemAbilityByName(*itemNamePtr);
        if (temp != nullptr)
            temp->init(shared_from_this(), mManaModel);
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
    currentMission.reset();
    monsterSpawner.reset();
    mManaModel = nullptr;
    Scene::clear();
}


