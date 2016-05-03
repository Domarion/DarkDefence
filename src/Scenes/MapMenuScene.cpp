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

