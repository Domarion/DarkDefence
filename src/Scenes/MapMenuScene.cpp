#include "MapMenuScene.h"
#include "../Input/InputDispatcher.h"
#include "../GlobalScripts/GameModel.h"

MapMenuScene::MapMenuScene()
   // :arialFont(new CFont())
{

}

MapMenuScene::~MapMenuScene()
{

}

void MapMenuScene::initScene(SceneManager *sceneManagerPtr)
{

     Renderer::getInstance()->setRendererDrawColor(255, 255, 255);
    if (!wasInited)
    {
        Scene::initScene(sceneManagerPtr);
        int curIndex =  GameModel::getInstance()->getCurrentMissionIndex();

        string s ="GameData/Missions/" + std::to_string(curIndex) +"/Mission.xml";
        GameModel::getInstance()->deserialize(currentMission, s);

        currentMissionView.init(currentMission, FontManager::getInstance()->getFontByKind("ButtonFont"));
        listGUI.push_back(&currentMissionView);

        mapIndicator.setRect(420, 0, 150, 48);
        mapIndicator.setIndicatorWidth(48);
        mapIndicator.setIndicatorHeight(48);
        mapIndicator.setCurrentMapIndex(curIndex);
        mapIndicator.setMapCount(3);//TODO missionCount
        mapIndicator.setCompletedTexture("GameData/textures/MapIndicator/completed.png");
        mapIndicator.setLockedTexture("GameData/textures/MapIndicator/locked.png");
        mapIndicator.setNormalTexture("GameData/textures/MapIndicator/normal.png");
        listGUI.push_back(&mapIndicator);

        //arialFont.setFont(currentMissionView.getFont());

        //arialFont.get()->loadFromFile("Fonts/arial.ttf", 24);


        mapPicture.setRect(400, 60, 400, Renderer::getInstance()->getScreenHeight() - 100);
        string mapImagePath = "GameData/Missions/" + std::to_string(curIndex) +"/mission.jpg";
        mapPicture.loadTexture(mapImagePath);
        listGUI.push_back(&mapPicture);


        loadButton.setFont(FontManager::getInstance()->getFontByKind("ButtonFont"));
        loadButton.setRect(Renderer::getInstance()->getScreenWidth() - 150, Renderer::getInstance()->getScreenHeight() - 30, 100, 30);
        loadButton.setText("Начать");
        string s0 = "GameScene";
        loadButton.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s0));
        listGUI.push_back(&loadButton);


        backButton.setFont(FontManager::getInstance()->getFontByKind("ButtonFont"));
        backButton.setRect(0, Renderer::getInstance()->getScreenHeight() - 30, 100, 30);
        backButton.setText("Назад");
        string s000 = "MainScene";
        backButton.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s000));
        listGUI.push_back(&backButton);
        wasInited = true;
    }
    InputDispatcher::getInstance()->addHandler(&loadButton);
    InputDispatcher::getInstance()->addHandler(&backButton);
}

void MapMenuScene::finalizeScene()
{

}

void MapMenuScene::startUpdate(double timestep)
{

}

