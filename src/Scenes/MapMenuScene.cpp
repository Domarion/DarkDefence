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
    if (!wasInited)
    {
        Scene::initScene(sceneManagerPtr);
        int curIndex =  GameModel::getInstance()->getCurrentMissionIndex();

        string s ="/home/kostya_hm/Projects/DarkDefence/GameData/Missions/" + std::to_string(curIndex) +"/Mission.xml";
        GameModel::getInstance()->deserialize(currentMission, s);

        currentMissionView.init(currentMission);
        listGUI.push_back(&currentMissionView);

        mapIndicator.setRect(200, 0, 150, 48);
        mapIndicator.setIndicatorWidth(48);
        mapIndicator.setIndicatorHeight(48);
        mapIndicator.setCurrentMapIndex(curIndex);
        mapIndicator.setMapCount(1);//TODO missionCount
        mapIndicator.setCompletedTexture(Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/MapIndicator/completed.png"));
        mapIndicator.setLockedTexture(Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/MapIndicator/locked.png"));
        mapIndicator.setNormalTexture(Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/MapIndicator/normal.png"));
        listGUI.push_back(&mapIndicator);

        TTF_Font* font = currentMissionView.getFont();
        SDL_Color color = {255, 255, 255};
        loadButton.setFont(font, color);
        loadButton.setRect(700, 550, 100, 50);
        loadButton.setText("Начать");
        string s0 = "GameScene";
        loadButton.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s0));
        listGUI.push_back(&loadButton);
    }
    InputDispatcher::getInstance()->addHandler(&loadButton);
}

void MapMenuScene::finalizeScene()
{

}

void MapMenuScene::startUpdate(double timestep)
{

}

