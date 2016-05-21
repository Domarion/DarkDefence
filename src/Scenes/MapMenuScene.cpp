#include "MapMenuScene.h"
#include "../Input/InputDispatcher.h"
#include "../GlobalScripts/GameModel.h"

MapMenuScene::MapMenuScene()
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

        currentMissionView.init(currentMission);
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

        arialFont.setFont(currentMissionView.getFont());

        loadButton.setFont(arialFont);
        loadButton.setRect(700, 550, 100, 50);
        loadButton.setText("Начать");
        string s0 = "GameScene";
        loadButton.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s0));
        listGUI.push_back(&loadButton);


        mapPicture.setRect(400, 60, 400, 440);
        string mapImagePath = "GameData/Missions/" + std::to_string(curIndex) +"/mission.jpg";
        mapPicture.loadTexture(mapImagePath);
        listGUI.push_back(&mapPicture);
    }
    InputDispatcher::getInstance()->addHandler(&loadButton);
}

void MapMenuScene::finalizeScene()
{

}

void MapMenuScene::startUpdate(double timestep)
{

}

