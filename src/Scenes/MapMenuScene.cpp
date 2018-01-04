#include "MapMenuScene.h"
#include "../GlobalScripts/GameModel.h"
#include "../GraphicsSystem/newSystem/UIElement/UIImage.h"
#include "../GraphicsSystem/newSystem/ConcreteUIViews/UIMissionView.h"
#include "../GlobalScripts/ResourceManager.h"
//#include "../GraphicsSystem/UI/MissionView.h"
//#include "../GraphicsSystem/UI/MapIndicator.h"

MapMenuScene::MapMenuScene(
    std::shared_ptr<RenderingSystem>& aRenderer,
    std::shared_ptr<InputDispatcher> aInputDispatcher)
    : Scene(aRenderer, aInputDispatcher)
    , currentMissionIndex(0)
    , currentMission()
{
}

void MapMenuScene::init(std::shared_ptr<SceneManager> sceneManagerPtr)
{
    Scene::init(sceneManagerPtr);
    renderer->setRendererDrawColor(0, 0, 0, 0);

    auto mapPicture =  std::make_shared<UIImage>(renderer);
    Size mapPictureSize = MainRect->getSize();
    std::string backgroundName {"MapMenuSceneBackground"};
    mapPicture->setTexture(ResourceManager::getInstance()->getTexture(backgroundName));
    mapPicture->setSize(mapPictureSize);
    MainRect->addChild(mapPicture);

    loadMissionView();
//     loadMapPicture();
//     initMapIndicators();

    initNavigationButtons();

    Scene::addToUIList(MainRect);
}


void MapMenuScene::clear()
{
    Scene::clear();
}

void MapMenuScene::initNavigationButtons()
{
    Scene::addLoadSceneButton("Назад", "TextFontButton", "MainScene",
                              0, MainRect->getSize().height - 50, 100, 50);

    Scene::addLoadSceneButton("Начать", "TextFontButton", "GameScene",
                              MainRect->getSize().width - 150, MainRect->getSize().height - 50, 100, 50);
}

void MapMenuScene::loadMissionView()
{
    currentMissionIndex =  GameModel::getInstance()->getCurrentMissionIndex();

    string s ="GameData/Missions/" + std::to_string(currentMissionIndex) +"/Mission.xml";
    GameModel::getInstance()->deserialize(currentMission, s);

    auto layout = std::make_shared<StubLayout>();

    auto currentMissionView = std::make_shared<UIMissionView>(renderer, layout);

    currentMissionView->setSize(Size(MainRect->getSize().width/4*3, MainRect->getSize().height - 100));
    currentMissionView->setScalingFactor(MainRect->getScalingFactor());
    currentMissionView->init(currentMission, FontManager::getInstance()->getFontByKind2("TextFontBig"));
    MainRect->addChild(currentMissionView);
}

//void MapMenuScene::loadMapPicture()
//{
//    auto mapPicture =  std::make_shared<UIImage>(renderer);
//    mapPicture->setPosition(Position(MainRect->getSize().width/4*3, 60));
//    Size mapPictureSize = MainRect->getSize();
//    mapPictureSize.width /= 4;
//    mapPictureSize.height -= 100;
//    mapPicture->setSize(mapPictureSize);
//    string mapImagePath = "GameData/Missions/" + std::to_string(currentMissionIndex) +"/mission.jpg";
//    mapPicture->loadTexture(mapImagePath);
//    MainRect->addChild(mapPicture);
//}

//void MapMenuScene::initMapIndicators()
//{
//    const int mapCount = 2;
//    const int indicatorsHeight = 48;
//    MapIndicator* mapIndicator = new MapIndicator(indicatorsHeight,
//                                                 indicatorsHeight,
//                                                 mapCount,
//                                                 currentMissionIndex);
//    mapIndicator->setRect(420, 0, 150, indicatorsHeight);

//    mapIndicator->setCompletedTexture("GameData/textures/MapIndicator/completed.png");
//    mapIndicator->setLockedTexture("GameData/textures/MapIndicator/locked.png");
//    mapIndicator->setNormalTexture("GameData/textures/MapIndicator/normal.png");

//    Scene::addToUIList(mapIndicator);
//}

