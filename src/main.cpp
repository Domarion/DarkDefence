/*
 * main.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */
#include "GameApp.h"

#include "Scenes/MainScene.h"
#include "Scenes/MapMenuScene.h"
#include "Scenes/GameScene.h"
#include "Scenes/InventoryScene.h"
#include "Scenes/ShopScene.h"
#include "Scenes/ScoreScene.h"
//#include "SaveData/DataGenerator.h"


int main( int argc, char* args[])
{

    /*DataGenerator dataGenerator;
    dataGenerator.saveItems();
    dataGenerator.saveMission();
    dataGenerator.saveMonsterCollection();
    dataGenerator.saveTowerTree();
    dataGenerator.saveMineCollection(;
*/

    SceneManager *sceneManager = new SceneManager();
    std::unique_ptr<GameApp> app(new GameApp(sceneManager));

    const int screenWidth = 800;
    const int screenHeight = 480;
    app->initLibrary(screenWidth, screenHeight);

	MainScene *mainScene = new MainScene();
    MapMenuScene *mapMenuScene = new MapMenuScene();
	GameScene *gameScene = new GameScene();
	InventoryScene *inventoryScene = new InventoryScene();
	ShopScene *shopScene = new ShopScene();
    ScoreScene* scoreScene = new ScoreScene();


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


