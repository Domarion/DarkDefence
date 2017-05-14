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
#include "../Input/InputDispatcher.h"
#include "../Utility/textfilefunctions.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImageButton.h"
#include "../GlobalScripts/ResourceManager.h"

#include "../GlobalConstants.h"
#include <sstream>
#include <cereal/archives/xml.hpp>

GameScene::GameScene(std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher)
    : Scene(aRenderer, aInputDispatcher)
    , gates(nullptr)
    , gatesHealthBar(nullptr)
    , manaBar(nullptr)
    , pointsLabel(nullptr)
    , waveLabel(nullptr)
    , monsterSpawner()
    , itemAbilitiesStorage()
    , towerUpgradeController(std::make_shared<TowerUpgradeController>())
    , tileMap(nullptr)
    , mManaModel(nullptr)
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

    if (counter <= 0)
    {
        bool result = GameModel::getInstance()->getResourcesModel()->removeResource(static_cast<int>(Enums::ResourceTypes::WHEAT), 5);

        if (!result && mManaModel)
        {
            if (!mManaModel->payMana(5))
            {
                if (gates)
                    gates->getDestructibleObject()->receiveDamageOneType(static_cast<int>(Enums::DamageTypes::dtPHYSICAL), 5);
            }
        }

        counter = 5000;
    }
    else
        counter -= timestep;

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

        GameModel::getInstance()->setMissionReward(currentMission.getReward());
        getParentSceneManager()->askForChangeScene(s1);
        return;
    }
    case MissionStatuses::mFAILED:
    {
        GameModel::getInstance()->setGameStatus(Enums::GameStatuses::gsLOST);
        std::string s2 = "ScoreScene";
        getParentSceneManager()->askForChangeScene(s2);
        return;
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

std::shared_ptr<ManaGlobal> GameScene::getManaModel() const
{
    return mManaModel;
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

    GameModel::getInstance()->loadMonsterList("GameData/MonsterList.xml");

    GameModel::getInstance()->loadTowerUpgrades("GameData/TowerTree.xml");

    GameModel::getInstance()->loadAbilitiesNames("GameData/abilities.txt");

    //TODO: Считывать размер ячейки матрицы из файла путей
    string tileMapMatrixPath = "GameData/Missions/" + std::to_string(curIndex) + "/map.txt";
    vector<vector<int> > aMapTemplate = androidText::loadMatrixFromFile(tileMapMatrixPath);
    tileMap = std::make_shared<TileMapManager>(aMapTemplate);

    string PositionsPath = "GameData/Missions/" + std::to_string(curIndex) + "/Positions.xml";

    string textString;
    androidText::loadTextFileToString(PositionsPath, textString);


    if (!textString.empty())
    {
        std::stringstream str(textString);


        cereal::XMLInputArchive xmlinp(str);
        xmlinp(cereal::make_nvp("Positions", mPositionsVector));
    }
}

void GameScene::initResourceView()
{
    auto resourcePanel = std::make_shared<ConcreteComposite>(renderer);
    //resourcePanel->setSize(Size(MainRect->getSize().width/3, 50));
    resourcePanel->setPosition(MainRect->getNextHorizontalPosition());

    const Size iconSize{48, 48};

    int resourcePanelWidth = iconSize.width * GlobalConstants::resourceTypeCount;

    Font labelFont = FontManager::getInstance()->getFontByKind2("TextFont");
    resourceLabels.resize(GlobalConstants::resourceTypeCount);
    for(size_t i = 0; i != GlobalConstants::resourceTypeCount; ++i)
    {
        string iconPath = "GameData/textures/Resources/"
                + GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(i) + ".png";

        auto resourceIcon = std::make_shared<UIImage>(renderer);
        resourceIcon->loadTexture(iconPath);
        resourceIcon->setSize(Size(48, 48));
        resourceIcon->setPosition(resourcePanel->getNextHorizontalPosition());
        resourcePanel->addChild(resourceIcon);

        string labelText = GameModel::getInstance()->getResourcesModel()->printResourceFromIndex(i);
        resourceLabels[i] = std::make_shared<UILabel>(labelText, labelFont, renderer);
        resourceLabels[i]->setPosition(resourcePanel->getNextHorizontalPosition());


        resourcePanel->addChild(resourceLabels[i]);
        resourcePanelWidth += resourceLabels[i]->getSize().width;
    }

    MainRect->addChild(resourcePanel);

    resourcePanel->setSize(Size(resourcePanelWidth + 5, iconSize.height));


}

void GameScene::initProgressBars()
{
    auto progressBarGroup = std::make_shared<ConcreteComposite>(renderer);
    progressBarGroup->setPosition(MainRect->getNextHorizontalPosition());

    Texture2D emptyBar(renderer);
    emptyBar.loadTexture("GameData/textures/EmptyBar.png");
    emptyBar.scaleToTexture();

    Texture2D gatesHealthBarFront(renderer);
    gatesHealthBarFront.loadTexture("GameData/textures/RedBar.png");
    gatesHealthBarFront.scaleToTexture();

    gatesHealthBar = std::make_shared<UIProgressBar>(renderer, emptyBar, gatesHealthBarFront);
    gatesHealthBar->calculateProgress(5000, 5000);
    progressBarGroup->addChild(gatesHealthBar);

    Texture2D manaBarFront(renderer);
    manaBarFront.loadTexture("GameData/textures/BlueBar.png");
    manaBarFront.scaleToTexture();

    manaBar = std::make_shared<UIProgressBar>(renderer, emptyBar, manaBarFront);
    manaBar->setPosition(progressBarGroup->getNextVerticalPosition());
    manaBar->calculateProgress(100, 100);
    progressBarGroup->addChild(manaBar);

    progressBarGroup->setSize(Size(manaBar->getSize().width, 2 * gatesHealthBar->getSize().height));
    MainRect->addChild(progressBarGroup);
}

void GameScene::copyToRender() const
{
    drawSceneObjects();
    if (SceneModeT::PlacingMode == mSceneMode)
    {
        renderer->setRendererDrawColor(0, 0, 255, 255);

        renderer->drawGrid(tileMap->getMapSize(), tileMap->getCellSize());
    }
    drawUI();
}

void GameScene::setGameSceneStatus(Enums::GameSceneStatuses aStatus)
{
    mGameSceneCurrentStatus = aStatus;
}

Enums::GameSceneStatuses GameScene::getGameSceneStatus() const
{
    return mGameSceneCurrentStatus;
}

void GameScene::setAbilityPlacingMode(const std::string& aAbilityName)
{
    if (mSceneMode == SceneModeT::StandardMode && spellStorage.setAbilityReady(aAbilityName))
    {
        if (spellStorage.canPlaceObjectAbility(aAbilityName))
        {
            mSceneMode = SceneModeT::PlacingMode;
        }
    }
}

void GameScene::placingCallBack()
{
    mSceneMode = SceneModeT::StandardMode;
}

void GameScene::spawningCallBack(std::string aMobName, Position aSpawnPosition)
{
    std::cout << "Entering placing" << std::endl;

    auto tileMapCopy = std::make_shared<TileMapManager>(*tileMap);
    auto someMob = std::make_shared<Mob>(GameModel::getInstance()->getMonsterByName(aMobName), tileMapCopy);

    if (someMob->getTileMapManager() == nullptr)
    {
        std::cout << "someMob->getTileMapManager = nullptr" << std::endl;
        return;
    }

    auto someSprite = std::make_shared<AnimationSceneSprite>(getRenderer());


    someSprite->setTexture(ResourceManager::getInstance()->getTexture(aMobName));    
    map<string, vector<SDL_Rect> > anims;

    std::string filename = "GameData/anims/Monsters/" + aMobName + ".anim";
    androidText::setRelativePath(filename);
    androidText::loadAnimFromFile(filename, anims);

    for(auto& anim : anims)
    {
        someSprite->setAnimRects(anim.first, anim.second);
    }

    someMob->setSprite(someSprite);
    spawnObject(aSpawnPosition.x, aSpawnPosition.y, someMob);
}

void GameScene::initTopPanel()
{
    initProgressBars();
    initResourceView();

    auto miniGroup = std::make_shared<ConcreteComposite>(renderer);
//    miniGroup->setSize(Size(MainRect->getSize().width/4, 50));
    miniGroup->setPosition(MainRect->getNextHorizontalPosition());

    Font aFont = FontManager::getInstance()->getFontByKind2("TextFont");

    pointsLabel = std::make_shared<UILabel>("none", aFont, renderer);
    pointsLabel->setPosition(miniGroup->getNextHorizontalPosition());

    miniGroup->addChild(pointsLabel);

    waveLabel = std::make_shared<UILabel>("nonenonenone", aFont, renderer);
    waveLabel->setPosition(miniGroup->getNextHorizontalPosition());
    miniGroup->addChild(waveLabel);

    MainRect->addChild(miniGroup);

    miniGroup->setSize(Size(pointsLabel->getSize().width + waveLabel->getSize().width + 50, waveLabel->getSize().height));
}

void GameScene::initAbilityCallBacks(const std::string& aAbilityName)
{
    auto abilityPtr = spellStorage.getAbilityModelWithName(aAbilityName);

    if (abilityPtr != nullptr)
    {
        abilityPtr->setPlacingCallback(std::bind(&GameScene::placingCallBack, this));
        auto abilityInputHandler = std::dynamic_pointer_cast<InputHandler>(abilityPtr);
        if (abilityInputHandler != nullptr)
        {
            mInputDispatcher->addHandler(abilityInputHandler);
        }
    }
}

void GameScene::initAbilitiesButtons()
{
    mManaModel = std::make_shared<ManaGlobal>();
    Size abilityButtonSize(96, 96);

    int abilityGroupHeight = static_cast<int>(abilityButtonSize.height * MainRect->getScalingFactor());
    Position abilityButtonPos(0, MainRect->getSize().height - abilityGroupHeight);//TODO:: убрать абсолютное позиционирование, сделать относительное

    spellStorage.loadWithScene(shared_from_this(), mManaModel);

    auto abilityButtonsGroup = std::make_shared<ConcreteComposite>(renderer);
    abilityButtonsGroup->setSize(Size(MainRect->getSize().width/3, abilityButtonSize.height));
    abilityButtonsGroup->setPosition(abilityButtonPos);
    abilityButtonsGroup->setScalingFactor(MainRect->getScalingFactor());

    size_t abilityButtonCount = GameModel::getInstance()->getAbilityCount();

    for(size_t i = 0; i < abilityButtonCount; ++i)
    {
        std::string abilityName = GameModel::getInstance()->getAbilityNameFromIndex(i);
        string imgPath = "GameData/textures/Abilities/Ability" + abilityName;

        string backPath = imgPath + "_back.png";
        string frontPath = imgPath + "_front.png";

        Texture2D background{renderer};
        Texture2D foreground{renderer};

        background.loadTexture(backPath);
        foreground.loadTexture(frontPath);

        const constexpr bool isVertical = true;
        auto abilityButton = std::make_shared<UIProgressBar>(renderer, background, foreground, isVertical);
        abilityButton->setSize(abilityButtonSize);
        abilityButton->setPosition(abilityButtonsGroup->getNextHorizontalPosition());

        abilityButton->ConnectMethod(std::bind(&GameScene::setAbilityPlacingMode, this, abilityName));

        abilityButtonsGroup->addChild(abilityButton);

        initAbilityCallBacks(abilityName);

        auto ability = spellStorage.getAbilityModelWithName(GameModel::getInstance()->getAbilityNameFromIndex(i));
        ability->connectCooldownListener
                (
                    std::bind
                    (
                        &UIProgressBar::calculateProgress,
                        abilityButton.get(),
                        std::placeholders::_1,
                        std::placeholders::_2
                    )
                );
    }

    MainRect->addChild(abilityButtonsGroup);

}

void GameScene::initUILayer()
{
    initTopPanel();

    Size buttonSize(72, 72);
    auto pauseButton = std::make_shared<UIImageButton>(renderer);
    pauseButton->setSize(buttonSize);
    pauseButton->setPosition(MainRect->getNextHorizontalPosition());
    pauseButton->loadTexture("GameData/textures/pause-button.png");
    pauseButton->ConnectMethod(std::bind(&GameScene::sendMessage, this, GlobalConstants::Paused));
    MainRect->addChild(pauseButton);

    auto resumeButton = std::make_shared<UIImageButton>(renderer);
    resumeButton->setSize(buttonSize);
    resumeButton->setPosition(MainRect->getNextHorizontalPosition());

    resumeButton->loadTexture("GameData/textures/resume-button.png");
    resumeButton->ConnectMethod(std::bind(&GameScene::sendMessage, this, GlobalConstants::Resumed));
    MainRect->addChild(resumeButton);

    Scene::addToUIList(MainRect);

    initAbilitiesButtons();
}

//void GameScene::placeResourcesPlaces()
//{
//    auto resPlace = std::make_shared<ResourcePlace>(700, Enums::ResourceTypes::STONE);
//    auto resSprite = std::make_shared<AnimationSceneSprite>(renderer);

//    resSprite->setSize(Size(100, 100));

//    string resourceName = GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(static_cast<int> (resPlace->getResourceType()));
//    string texturePath = "GameData/textures/Resources/" + resourceName + "Resource.png";
//    resSprite->loadTexture(texturePath);
//    resPlace->setSprite(resSprite);
//    resPlace->setName("ResourcePlace");
//    resPlace->setTag("ResourcePlace");
//    spawnObject(400, 100, resPlace);
//}

//void GameScene::placeCastle()
//{
//    auto newView = std::make_shared<AnimationSceneSprite>(renderer);

//     newView->setTexture(ResourceManager::getInstance()->getTexture("Castle"));
//     gates = std::make_shared<Gates>();
//     gates->setSprite(newView);
//     gates->setTag("Gates");
//     gates->getDestructibleObject()->connectMethod(std::bind(&UIProgressBar::calculateProgress, gatesHealthBar, std::placeholders::_1, std::placeholders::_2));
//     gates->getDestructibleObject()->setMaximumHealth(5000);
//     spawnObject(40, 100, gates);
//}

//void GameScene::placeTowers()
//{
//    towerUpgradeController->init(shared_from_this(), renderer);

//    list<string> towerNames = {"WatcherTower","BallistaTower", "CatapultTower", "MageTower", "ProductivityTower",
//                               "WindTower", "EarthTower","CloudTower"};
//    int x = 10;
//    for(const auto& towerName : towerNames)
//    {
//        std::shared_ptr<Tower> tower= towerFabric.produceTower(towerName, renderer, towerUpgradeController, tileMap);
//        spawnObject(x, 300, tower);
//        x+= 60;
//    }

//}

void GameScene::placeSceneObjects()//TODO: Найти лучшее решение для считывания и хранения позиций объектов
{

    int curMissionIndex =  GameModel::getInstance()->getCurrentMissionIndex();

    std::string terrainPath = "GameData/textures/Missions/" + std::to_string(curMissionIndex) + ".png";
    std::shared_ptr<SceneObject> Terrain = objectFabric.produce("Terrain", "none", terrainPath, 0 , 0, renderer );
    spawnObject(0,0, Terrain);

    towerUpgradeController->init(shared_from_this(), renderer);

    for(const auto& item : mPositionsVector)
    {
        if (item.Name.find("Tower") != std::string::npos)
        {
            std::shared_ptr<Tower> tower= towerFabric.produceTower(item.Name, renderer, towerUpgradeController, tileMap);
            tower->getSprite()->setAnchorPointPlace(item.xCoordAnchorType, item.yCoordAnchorType);

            spawnObject(item.ImagePosition.x, item.ImagePosition.y, tower);
        }
        else
            if (item.Name == "Gates")
                {
                    auto newView = std::make_shared<AnimationSceneSprite>(renderer);

                     newView->setSize(item.ImageSize);
					 newView->setTexture(ResourceManager::getInstance()->getTexture("Castle"));

                     newView->setAnchorPointPlace(item.xCoordAnchorType, item.yCoordAnchorType);

                     gates = std::make_shared<Gates>();
                     gates->setSprite(newView);
                     gates->setTag("Gates");
                     gates->getDestructibleObject()->connectMethod(std::bind(&UIProgressBar::calculateProgress, gatesHealthBar, std::placeholders::_1, std::placeholders::_2));
                     gates->getDestructibleObject()->setMaximumHealth(5000);
                     spawnObject(item.ImagePosition.x, item.ImagePosition.y, gates);
                }
                else
                    if (item.Name == "ResourceWheat")
                    {
                        auto resPlace = std::make_shared<ResourcePlace>(700, Enums::ResourceTypes::WHEAT);
                        auto resSprite = std::make_shared<AnimationSceneSprite>(renderer);

                        resSprite->setSize(item.ImageSize);

                        resSprite->setAnchorPointPlace(item.xCoordAnchorType, item.yCoordAnchorType);

                        string resourceName = GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(static_cast<int> (resPlace->getResourceType()));
                        string texturePath = "GameData/textures/Resources/" + resourceName + "Resource.png";
                        resSprite->loadTexture(texturePath);
                        resPlace->setSprite(resSprite);
                        resPlace->setName("ResourcePlace");
                        resPlace->setTag("ResourcePlace");
                        spawnObject(item.ImagePosition.x, item.ImagePosition.y, resPlace);
                    }
                    else
                        if (item.Name == "Spawner")
                        {
                            auto spawnerSprite = std::make_shared<AnimationSceneSprite>(renderer);

                            spawnerSprite->setSize(item.ImageSize);
                            spawnerSprite->setAnchorPointPlace(item.xCoordAnchorType, item.yCoordAnchorType);


                            string spawnertexturePath = "GameData/textures/spawner.png";
                            spawnerSprite->loadTexture(spawnertexturePath);
                            monsterSpawner = std::make_shared<Spawner>();
                            monsterSpawner->setSprite(spawnerSprite);
                            monsterSpawner->setName("Spawner");
                            monsterSpawner->setTag("Spawner");
                            monsterSpawner->loadWavesInfo();

                            spawnObject(item.ImagePosition.x, item.ImagePosition.y, monsterSpawner);

                            monsterSpawner->connectInfoProcesser(
                                std::bind(&GameScene::processWaveInfo, this, std::placeholders::_1));
                            monsterSpawner->connectSpawnCallBack(
                                std::bind(
                                    &GameScene::spawningCallBack, this, std::placeholders::_1, std::placeholders::_2));

                        }
        }
}

void GameScene::applyArtefactEffects()
{
    vector<string> itemNames = GameModel::getInstance()->getHeroInventory()->getItemNames();
    itemAbilitiesStorage.loadItemAbilities();

    for(const auto& itemName : itemNames)
    {
        auto temp = itemAbilitiesStorage.getItemAbilityByName(itemName);
        if (temp != nullptr)
            temp->init(shared_from_this(), mManaModel);
    }

}

void GameScene::processWaveInfo(std::string aInfo)
{
    if (waveLabel == nullptr || aInfo == "none")
    {
        return;
    }

    if (aInfo != "InProgress")
    {
        waveLabel->setText(aInfo);
    }

    if (aInfo == "InProgress" || aInfo != "No more waves")
    {
        if (tileMap == nullptr)
        {
            std::cout << "TileIsNullinGameScene" << std::endl;
        }
        monsterSpawner->doSpawn();
        return;
    }

    monsterSpawner->disconnectInfoProcesser();
    monsterSpawner->disconnectSpawnCallback();

    GameModel::getInstance()->setGameStatus(Enums::GameStatuses::gsWON);
    GameModel::getInstance()->setMissionReward(currentMission.getReward());
    std::string s2 = "ScoreScene";
    getParentSceneManager()->askForChangeScene(s2);
}



void GameScene::clear()
{
    pointsLabel = nullptr;
    waveLabel = nullptr;
    manaBar = nullptr;
    gatesHealthBar = nullptr;
    gates = nullptr;
    currentMission.reset();
    if (monsterSpawner)
    {
        monsterSpawner->disconnectInfoProcesser();
        monsterSpawner->disconnectSpawnCallback();

        monsterSpawner.reset();
    }
    mManaModel = nullptr;
    GameModel::getInstance()->getResourcesModel()->loadFromFile("GameData/resources.txt");
    mGameSceneCurrentStatus = Enums::GameSceneStatuses::Default;
    mSceneMode = SceneModeT::StandardMode;
    Scene::clear();
}


