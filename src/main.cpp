/*
 * main.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "SDL_Engine.h"
#include "GameApp.h"
#include "GraphicsSystem/newSystem/RenderingSystem.h"
#include "Scenes/MainScene.h"
#include "Scenes/MapMenuScene.h"
#include "Scenes/GameScene.h"
#include "Scenes/InventoryScene.h"
#include "Scenes/ShopScene.h"
#include "Scenes/ScoreScene.h"
//#include "SaveData/DataGenerator.h"


int main( int argc, char* args[])
{

  /* DataGenerator dataGenerator;
    dataGenerator.saveTowerTree();
  dataGenerator.saveItems();
    dataGenerator.saveMission();
    dataGenerator.saveMonsterCollection();

    dataGenerator.saveMineCollection();*/

    auto SDL2_Library = std::make_unique<SDL2Engine::SDL2>(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);


    Size screenSize(800, 480);
    auto Renderer = std::make_shared<RenderingSystem>(screenSize);
    SceneManager *sceneManager = new SceneManager();
    std::unique_ptr<GameApp> app = std::make_unique<GameApp>(sceneManager, Renderer);

    MainScene *mainScene = new MainScene(Renderer);
    MapMenuScene *mapMenuScene = new MapMenuScene(Renderer);
    GameScene *gameScene = new GameScene(Renderer);
    InventoryScene *inventoryScene = new InventoryScene(Renderer);
    ShopScene *shopScene = new ShopScene(Renderer);
    ScoreScene* scoreScene = new ScoreScene(Renderer);


    sceneManager->addScene(mainScene, "MainScene");
    sceneManager->addScene(mapMenuScene, "MapMenuScene");
	sceneManager->addScene(gameScene, "GameScene");

    gameScene->ConnectMethod(std::bind(&GameApp::receiveMessage, app.get(), std::placeholders::_1));
	sceneManager->addScene(inventoryScene, "InventoryScene");
	sceneManager->addScene(shopScene, "ShopScene");
    sceneManager->addScene(scoreScene, "ScoreScene");

    sceneManager->setCurrentSceneByName("MainScene");

    int result = app->gameLoop();

	return result;
}


