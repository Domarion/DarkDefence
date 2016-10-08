#include "MapMenuScene.h"
#include "../GlobalScripts/GameModel.h"
#include "../GraphicsSystem/UI/MissionView.h"
#include "../GraphicsSystem/UI/TextButton.h"
#include "../GraphicsSystem/UI/MapIndicator.h"

MapMenuScene::MapMenuScene(std::shared_ptr<RenderingSystem> &aRenderer)
   :Scene(aRenderer)
   , currentMissionIndex(0)
{

}

MapMenuScene::~MapMenuScene()
{

}

void MapMenuScene::init(SceneManager *sceneManagerPtr)
{
     Scene::init(sceneManagerPtr);
     renderer->setRendererDrawColor(255, 255, 255, 255);
     loadMissionView();
     loadMapPicture();
     initMapIndicators();
     initNavigationButtons();
}


void MapMenuScene::clear()
{
    Scene::clear();

}

void MapMenuScene::initNavigationButtons()
{
    TextButton* backButton = new TextButton();
    backButton->setFont(FontManager::getInstance()->getFontByKind("ButtonFont"));
   // backButton->setPos(0, Renderer::getInstance()->getScreenHeight() - 30);
    backButton->setText("Назад");
    string s000 = "MainScene";
    backButton->ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, getParentSceneManager(), s000));
    //Scene::addToUIList(backButton);

    TextButton* loadButton = new TextButton();
    loadButton->setFont(FontManager::getInstance()->getFontByKind("ButtonFont"));
   // loadButton->setPos(Renderer::getInstance()->getScreenWidth() - 150, Renderer::getInstance()->getScreenHeight() - 30);
    loadButton->setText("Начать");
    string s0 = "GameScene";
    loadButton->ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, getParentSceneManager(), s0));
//    Scene::addToUIList(loadButton);


}

void MapMenuScene::loadMissionView()
{

    currentMissionIndex =  GameModel::getInstance()->getCurrentMissionIndex();

    string s ="GameData/Missions/" + std::to_string(currentMissionIndex) +"/Mission.xml";
    GameModel::getInstance()->deserialize(currentMission, s);

    MissionView* currentMissionView = new MissionView();
    currentMissionView->init(currentMission, FontManager::getInstance()->getFontByKind("ButtonFont"));
//    Scene::addToUIList(currentMissionView);


}

void MapMenuScene::loadMapPicture()
{
    CTexture* mapPicture = new CTexture();
    //mapPicture->setRect(400, 60, 400, Renderer::getInstance()->getScreenHeight() - 100);
    string mapImagePath = "GameData/Missions/" + std::to_string(currentMissionIndex) +"/mission.jpg";
    mapPicture->loadTexture(mapImagePath);
//    Scene::addToUIList(mapPicture);
}

void MapMenuScene::initMapIndicators()
{
    const int mapCount = 2;
    const int indicatorsHeight = 48;
    MapIndicator* mapIndicator = new MapIndicator(indicatorsHeight,
                                                 indicatorsHeight,
                                                 mapCount,
                                                 currentMissionIndex);
    mapIndicator->setRect(420, 0, 150, indicatorsHeight);

    mapIndicator->setCompletedTexture("GameData/textures/MapIndicator/completed.png");
    mapIndicator->setLockedTexture("GameData/textures/MapIndicator/locked.png");
    mapIndicator->setNormalTexture("GameData/textures/MapIndicator/normal.png");

//    Scene::addToUIList(mapIndicator);
}

