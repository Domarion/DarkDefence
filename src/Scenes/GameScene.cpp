#include <cmath>
#include <iostream>
#include <sstream>

#include <boost/optional.hpp>
#include <cereal/archives/xml.hpp>
#include <SDL.h>

#include "../GlobalScripts/GameModel.h"
#include "../GlobalScripts/ResourceManager.h"

#include "../GlobalConstants.h"

#include "../GraphicsSystem/newSystem/UIElement/UIImageButton.h"

#include "../Input/InputDispatcher.h"
#include "../Input/SceneInputHandler.h"

#include "../Mob/Tower.h"

#include "../Utility/textfilefunctions.h"

#include "GameScene.h"
#include "Logging/Logger.h"

GameScene::GameScene(std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher)
    : Scene(aRenderer, aInputDispatcher)
{
}

void GameScene::init()
{
    Scene::init();
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
        bool result =
            GameModel::getInstance()->getResourcesModel()->removeResource(
                Enums::toIntegralType(Enums::ResourceTypes::WHEAT), 5);

        if (!result && mManaModel)
        {
            if (!mManaModel->payMana(5))
            {
                if (gates)
                {
                    gates->getDestructibleObject()->receiveDamageOneType(
                        Enums::toIntegralType(Enums::DamageTypes::dtPHYSICAL), 5);
                }
            }
        }

        counter = 5000;
    }
    else
    {
        counter -= timestep;
    }

    if (gates != nullptr && gates->getDestructibleObject() != nullptr)
    {
        switch(currentMission.checkStatus(GameModel::getInstance()->getGameStatus()))
        {
        case MissionStatuses::mIN_PROGRESS:
        case MissionStatuses::mNOT_STARTED:
        {
            break;
        }
        case MissionStatuses::mCOMPLETED:
        {
            GameModel::getInstance()->setGameStatus(Enums::GameStatuses::gsWON);
            std::string s1 = "ScoreScene";

            GameModel::getInstance()->setMissionReward(currentMission.getReward());
            askForChangeScene(s1);
            return;
        }
        case MissionStatuses::mFAILED:
        {
            GameModel::getInstance()->setGameStatus(Enums::GameStatuses::gsLOST);
            std::string s2 = "ScoreScene";
            askForChangeScene(s2);
            return;
        }
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

const map<string, std::shared_ptr<AbilityModel>>& GameScene::getAbilityModelList() const
{
    return spellStorage.getAbilityModelList();
}

void GameScene::ConnectMethod(std::function<void (string)> handler)
{
    method = handler;
}

const std::shared_ptr<AbilityModel>& GameScene::getAbilityModelWithName(const std::string& aName)
{
    return spellStorage.getAbilityModelWithName(aName);
}

void GameScene::sendMessage(string msgText)
{
    if (method != nullptr)
    {
        method(msgText);
    }
}

const std::shared_ptr<ManaGlobal>& GameScene::getManaModel() const
{
    return mManaModel;
}

void GameScene::loadData()
{
    auto& missionSwitcher = GameModel::getInstance()->getMissionSwitcher();
    auto mission = missionSwitcher.getCurrentMission();

    assert(mission);
    if (mission)
    {
        currentMission = *mission;
    }

    currentMissionPath = "GameData/Missions/" + currentMission.getCaption();

    std::string pointsConf = currentMissionPath + std::string{"/points.txt"};
    GameModel::getInstance()->loadMonsterPointsList(pointsConf);

    std::string resourcesConf = currentMissionPath + std::string{"/resources.txt"};
    GameModel::getInstance()->getResourcesModel()->loadFromFile(resourcesConf);

    std::string mineModelsConf = "GameData/MineModels.xml";
    GameModel::getInstance()->loadMinesList(mineModelsConf);

    GameModel::getInstance()->loadMonsterList("GameData/MonsterList.xml");

    GameModel::getInstance()->loadTowerUpgrades("GameData/TowerTree.xml");

    GameModel::getInstance()->loadAbilitiesNames("GameData/abilities.txt");

    //TODO: Считывать размер ячейки матрицы из файла путей
    string tileMapMatrixPath = "GameData/Missions/" + currentMission.getCaption() + "/map.txt";
    vector<vector<int> > aMapTemplate = androidText::loadMatrixFromFile(tileMapMatrixPath);
    tileMap = std::make_shared<TileMapManager>(aMapTemplate);

    string PositionsPath = "GameData/Missions/" + currentMission.getCaption() + "/Positions.xml";

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
    auto layout = std::make_shared<StubLayout>();
    auto resourcePanel = std::make_shared<ConcreteComposite>(renderer, layout);
    resourcePanel->setPosition(MainRect->getNextHorizontalPosition());

    // TODO нужно как-то убрать использование размера из кода
    const Size iconSize{48, 48};

    size_t resourcePanelWidth = iconSize.width * GlobalConstants::resourceTypeCount;

    const auto& labelFont = FontManager::getInstance()->getFontByKind2("TextFont");
    resourceLabels.resize(GlobalConstants::resourceTypeCount);

    for(size_t i = 0; i != GlobalConstants::resourceTypeCount; ++i)
    {
        string resourceName = GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(i);

        auto resourceIcon = std::make_shared<UIImage>(renderer);
        resourceIcon->setTexture(ResourceManager::getInstance()->getTexture(resourceName));

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
    auto layout = std::make_shared<StubLayout>();

    auto progressBarGroup = std::make_shared<ConcreteComposite>(renderer, layout);
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

GameScene::SceneModeT GameScene::getSceneMode() const
{
    return mSceneMode;
}

const std::shared_ptr<TileMapManager>& GameScene::getTileMap() const
{
    return tileMap;
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

void GameScene::spawningCallBack(std::string aMobName, Position aSpawnPosition, size_t aDrawPriority)
{
    static int counter11 = 0;

    ++counter11;

    auto tileMapCopy = std::make_shared<TileMapManager>(*tileMap);
    auto someMob = std::make_shared<Mob>(GameModel::getInstance()->getMonsterByName(aMobName), tileMapCopy);

    if (someMob->getTileMapManager() == nullptr)
    {
        return;
    }

    if (!ResourceManager::getInstance()->hasAnimationPack(aMobName))
    {
        LOG_ERROR(std::string("No animation in anim pack for: ")+ aMobName);

        throw std::runtime_error("No animation in anim pack.");
    }
    auto& animPack = ResourceManager::getInstance()->getAnimationPack(aMobName);
    auto someSprite = std::make_shared<AnimationSceneSprite>(getRenderer(), AnimationSceneSprite::Animation{animPack});

    someSprite->setTexture(ResourceManager::getInstance()->getTexture(aMobName));

    someMob->setSprite(someSprite);
    someMob->setDrawPriority(aDrawPriority);

    spawnObject(aSpawnPosition, someMob);
}

void GameScene::initTopPanel()
{
    initProgressBars();
    initResourceView();

    auto layout = std::make_shared<StubLayout>();
    auto miniGroup = std::make_shared<ConcreteComposite>(renderer, layout);
    miniGroup->setPosition(MainRect->getNextHorizontalPosition());

    const auto& aFont = FontManager::getInstance()->getFontByKind2("TextFont");

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
    Position abilityButtonPos(0, MainRect->getSize().height -
                              abilityGroupHeight);//TODO:: убрать абсолютное позиционирование, сделать относительное

    spellStorage.loadWithScene(shared_from_this(), mManaModel);

    auto layout = std::make_shared<StubLayout>();

    auto abilityButtonsGroup = std::make_shared<ConcreteComposite>(renderer, layout);
    abilityButtonsGroup->setSize(Size(MainRect->getSize().width/3, abilityButtonSize.height));
    abilityButtonsGroup->setPosition(abilityButtonPos);
    abilityButtonsGroup->setScalingFactor(MainRect->getScalingFactor());

    size_t abilityButtonCount = GameModel::getInstance()->getAbilityCount();

    for(size_t i = 0; i < abilityButtonCount; ++i)
    {
        const auto& abilityName = GameModel::getInstance()->getAbilityNameFromIndex(i);
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

//TODO: Найти лучшее решение для считывания и хранения позиций объектов
void GameScene::placeSceneObjects()
{
    //TODO Продумать предзагрузку динамически меняющихся объектов

    std::string terrainPath = "GameData/textures/Missions/" + currentMission.getCaption() + ".png";
    std::shared_ptr<SceneObject> Terrain = objectFabric.produce("Terrain", "none", terrainPath, 0, 0, renderer );
    auto inputHandler = std::make_shared<SceneInputHandler>();
    if (inputHandler)//TODO не перехватывать весь ввод, чтобы можно было нажимать на кнопки или башни
    {
        inputHandler->setParentScene(shared_from_this());
        Terrain->setInputHandler(inputHandler);
    }
    spawnObject(Position::Zero(), Terrain);

    towerUpgradeController = std::make_shared<TowerUpgradeController>();
    assert(towerUpgradeController);
    towerUpgradeController->init(shared_from_this(), renderer);

    for(const auto& item : mPositionsVector)
    {
        if (item.Name.find("Tree") != std::string::npos)
        {
            auto someObject = std::make_shared<SceneObject>();
            auto someSprite = std::make_shared<AnimationSceneSprite>(renderer);

            someSprite->setTexture(ResourceManager::getInstance()->getTexture("Tree"));
            someSprite->setAnchorPointPlace(item.xCoordAnchorType, item.yCoordAnchorType);
            someSprite->setSize(item.ImageSize);
            someObject->setSprite(someSprite);
            someObject->setTag("Enviroment");
            someObject->setDrawPriority(item.DrawPriority);

            spawnObject(item.ImagePosition, someObject);
        }
        else if (item.Name.find("Tower") != std::string::npos)
        {
            auto tower= towerUpgradeController->ProduceTower(item.Name, tileMap, item.DrawPriority);
            tower->getSprite()->setAnchorPointPlace(item.xCoordAnchorType, item.yCoordAnchorType);

            spawnObject(item.ImagePosition, tower);
        }
        else if (item.Name == "Gates")
        {
            auto newView = std::make_shared<AnimationSceneSprite>(renderer);

            newView->setSize(item.ImageSize);
            newView->setTexture(ResourceManager::getInstance()->getTexture("Castle"));

            newView->setAnchorPointPlace(item.xCoordAnchorType, item.yCoordAnchorType);

            gates = std::make_shared<Gates>();
            gates->setSprite(newView);
            gates->setTag("Gates");
            gates->getDestructibleObject()->connectMethod(
                std::bind
                (
                    &UIProgressBar::calculateProgress,
                    gatesHealthBar,
                    std::placeholders::_1,
                    std::placeholders::_2
                ));
            gates->getDestructibleObject()->setMaximumHealth(5000);
            gates->setDrawPriority(item.DrawPriority);
            spawnObject(item.ImagePosition, gates);
        }
        else if (item.Name == "ResourceWheat")
        {
            auto resPlace = std::make_shared<ResourcePlace>(700, Enums::ResourceTypes::WHEAT);
            auto resSprite = std::make_shared<AnimationSceneSprite>(renderer);

            resSprite->setAnchorPointPlace(item.xCoordAnchorType, item.yCoordAnchorType);

            string resourcePlaceName =
                GameModel::getInstance()->getResourcesModel()->getResourceNameFromType(resPlace->getResourceType());
            resourcePlaceName.append("Resource");

            resSprite->setTexture(ResourceManager::getInstance()->getTexture(resourcePlaceName));
            resSprite->setSize(item.ImageSize);
            resPlace->setSprite(resSprite);
            resPlace->setName("ResourcePlace");
            resPlace->setTag("ResourcePlace");
            resPlace->setDrawPriority(item.DrawPriority);

            spawnObject(item.ImagePosition, resPlace);
        }
        else if (item.Name == "ResourceStone")
        {
            auto resPlace = std::make_shared<ResourcePlace>(300, Enums::ResourceTypes::STONE);
            auto resSprite = std::make_shared<AnimationSceneSprite>(renderer);

            resSprite->setAnchorPointPlace(item.xCoordAnchorType, item.yCoordAnchorType);

            string resourcePlaceName =
                GameModel::getInstance()->getResourcesModel()->getResourceNameFromType(resPlace->getResourceType());
            resourcePlaceName.append("Resource");

            resSprite->setTexture(ResourceManager::getInstance()->getTexture(resourcePlaceName));
            resSprite->setSize(item.ImageSize);
            resPlace->setSprite(resSprite);
            resPlace->setName("ResourcePlace");
            resPlace->setTag("ResourcePlace");
            resPlace->setDrawPriority(item.DrawPriority);

            spawnObject(item.ImagePosition, resPlace);
        }
        else if (item.Name == "Spawner")
        {
            auto spawnerSprite = std::make_shared<AnimationSceneSprite>(renderer);

            spawnerSprite->setTexture(ResourceManager::getInstance()->getTexture("Spawner"));
            spawnerSprite->setSize(item.ImageSize);
            spawnerSprite->setAnchorPointPlace(item.xCoordAnchorType, item.yCoordAnchorType);

            monsterSpawner = std::make_shared<Spawner>();
            monsterSpawner->setSprite(spawnerSprite);
            monsterSpawner->setName("Spawner");
            monsterSpawner->setTag("Spawner");
            std::string waveInfoPath = currentMissionPath + "/wavesInfo.txt";
            monsterSpawner->loadWavesInfo(waveInfoPath);

            monsterSpawner->setDrawPriority(item.DrawPriority);

            spawnObject(item.ImagePosition, monsterSpawner);

            monsterSpawner->connectInfoProcesser(
                std::bind(&GameScene::processWaveInfo, this, std::placeholders::_1));
            monsterSpawner->connectSpawnCallBack(
                std::bind(
                    &GameScene::spawningCallBack,
                    this,
                    std::placeholders::_1,
                    std::placeholders::_2,
                    std::placeholders::_3)
                );
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
    if (waveLabel == nullptr || aInfo.empty() || aInfo == "none")
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
        }
        monsterSpawner->doSpawn();
        return;
    }

    monsterSpawner->disconnectInfoProcesser();
    monsterSpawner->disconnectSpawnCallback();

    GameModel::getInstance()->setGameStatus(Enums::GameStatuses::gsWON);
    GameModel::getInstance()->setMissionReward(currentMission.getReward());
    std::string s2 = "ScoreScene";
    askForChangeScene(s2);
}

void GameScene::clear()
{
    pointsLabel = nullptr;
    waveLabel = nullptr;
    manaBar = nullptr;
    gatesHealthBar = nullptr;
    gates = nullptr;
    currentMission.reset();
    towerUpgradeController.reset();
    currentMissionPath.clear();
    if (monsterSpawner)
    {
        monsterSpawner->disconnectInfoProcesser();
        monsterSpawner->disconnectSpawnCallback();

        monsterSpawner.reset();
    }

    mManaModel = nullptr;
    mGameSceneCurrentStatus = Enums::GameSceneStatuses::Default;
    mSceneMode = SceneModeT::StandardMode;
    Scene::clear();
}
