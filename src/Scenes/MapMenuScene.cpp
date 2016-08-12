#include "MapMenuScene.h"
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

     if (wasInited)
     {
         wasInited = false;
         mapIndicator.free();
         Scene::clearUIList();
         mapPicture.free();
         currentMissionView.free();
     }


    if (!wasInited)
    {
        Scene::initScene(sceneManagerPtr);
        int curIndex =  GameModel::getInstance()->getCurrentMissionIndex();

        string s ="GameData/Missions/" + std::to_string(curIndex) +"/Mission.xml";
        GameModel::getInstance()->deserialize(currentMission, s);

        currentMissionView.init(currentMission, FontManager::getInstance()->getFontByKind("ButtonFont"));
        Scene::addToUIList(&currentMissionView);

        mapIndicator.setRect(420, 0, 150, 48);
        mapIndicator.setIndicatorWidth(48);
        mapIndicator.setIndicatorHeight(48);
        mapIndicator.setCurrentMapIndex(curIndex);
        mapIndicator.setMapCount(3);//TODO missionCount
        mapIndicator.setCompletedTexture("GameData/textures/MapIndicator/completed.png");
        mapIndicator.setLockedTexture("GameData/textures/MapIndicator/locked.png");
        mapIndicator.setNormalTexture("GameData/textures/MapIndicator/normal.png");
        Scene::addToUIList(&mapIndicator);

        //arialFont.setFont(currentMissionView.getFont());

        //arialFont.get()->loadFromFile("Fonts/arial.ttf", 24);


        mapPicture.setRect(400, 60, 400, Renderer::getInstance()->getScreenHeight() - 100);
        string mapImagePath = "GameData/Missions/" + std::to_string(curIndex) +"/mission.jpg";
        mapPicture.loadTexture(mapImagePath);
        Scene::addToUIList(&mapPicture);


        loadButton.setFont(FontManager::getInstance()->getFontByKind("ButtonFont"));
        loadButton.setPos(Renderer::getInstance()->getScreenWidth() - 150, Renderer::getInstance()->getScreenHeight() - 30);
        loadButton.setText("Начать");
        string s0 = "GameScene";
        loadButton.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s0));
        Scene::addToUIList(&loadButton);


        backButton.setFont(FontManager::getInstance()->getFontByKind("ButtonFont"));
        backButton.setPos(0, Renderer::getInstance()->getScreenHeight() - 30);
        backButton.setText("Назад");
        string s000 = "MainScene";
        backButton.ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, sceneManagerPtr, s000));
        Scene::addToUIList(&backButton);
        wasInited = false;
    }

}

void MapMenuScene::finalizeScene()
{

}

void MapMenuScene::startUpdate(double timestep)
{

}

void MapMenuScene::resetState()
{
    mapPicture.free();
    currentMissionView.finalize();
    Scene::resetState();
}

