/*
 * GameApp.cpp
 *
 *  Created on: 9 марта 2016 г.
 *      Author: kostya_hm
 */

#include "GameApp.h"
#include <iostream>
using std::cout;
using std::endl;
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <exception>
#include "Input/InputDispatcher.h"
#include "Grouping/FontManager.h"
#include "GlobalConstants.h"

#include "Scenes/MainScene.h"
#include "Scenes/MapMenuScene.h"
#include "Scenes/GameScene.h"
#include "Scenes/InventoryScene.h"
#include "Scenes/ShopScene.h"
#include "Scenes/ScoreScene.h"
#include <string>
GameApp::GameApp(std::unique_ptr<SceneManager> aSceneManager, std::unique_ptr<RenderingSystem> aRenderer)
: mRenderer(std::move(aRenderer))
, mSceneManager(std::move(aSceneManager))
, paused(false)
{
    FontManager::getInstance()->loadFontList("GameData/fontconfig.txt");

}

void GameApp::addScenes()
{
    auto mainScene = std::make_unique<MainScene>(mRenderer);
    auto mapMenuScene = std::make_unique<MapMenuScene>(mRenderer);
    auto gameScene = std::make_unique<GameScene>(mRenderer);
    auto inventoryScene = std::make_unique<InventoryScene>(mRenderer);
    auto shopScene = std::make_unique<ShopScene>(mRenderer);
    auto scoreScene = std::make_unique<ScoreScene>(mRenderer);

    gameScene->ConnectMethod(std::bind(&GameApp::receiveMessage, this, std::placeholders::_1));

    mSceneManager->addScene(std::move(mainScene), "MainScene");
    mSceneManager->addScene(std::move(mapMenuScene), "MapMenuScene");
    mSceneManager->addScene(std::move(gameScene), "GameScene");

    mSceneManager->addScene(std::move(inventoryScene), "InventoryScene");
    mSceneManager->addScene(std::move(shopScene), "ShopScene");
    mSceneManager->addScene(std::move(scoreScene), "ScoreScene");

    mSceneManager->setCurrentSceneByName("MainScene");
}


int GameApp::gameLoop()
{

    int lasttime = SDL_GetTicks();
    const int MS_PER_UPDATE = 16;//1000ms/60FPS
    int lag = 0;
    bool quit = false;

    try
    {
        while(!quit)
        {
            int currenttime = SDL_GetTicks();
            quit = processInput();

            if (!isPaused())
            {
                int elapsed = currenttime - lasttime;
                lasttime = currenttime;
                lag += elapsed;

                while (lag >= MS_PER_UPDATE)
                {
                    updateScene(mSceneManager->getCurrentScene(), MS_PER_UPDATE);
                    lag -= MS_PER_UPDATE;
                }
            }
            else
                lasttime = currenttime;

            renderScene(mSceneManager->getCurrentScene());
        }
    }
    catch (std::exception &ex)
    {
        cout << "Exception: " << ex.what() << endl;
        return 1;
    }

	return 0;
}

int GameApp::renderScene(std::shared_ptr<Scene> scene)
{
    if (mRenderer != nullptr)
    {

        mRenderer->renderClear();

        if (scene != nullptr)
        {
            scene->copyToRender();
        }
        else
            cout << "Scene is null!" << endl;

        mRenderer->renderPresent();

    }

    return 0;
}

bool GameApp::isPaused()
{
    return paused;
}

void GameApp::updateScene(std::shared_ptr<Scene> scene, double timestep)
{
    if (scene != nullptr)
        scene->startUpdate(timestep);
}

bool GameApp::processInput()
{
    bool needQuit = false;

    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            //bsceneManager->getCurrentScene()->onGameQuit();
            needQuit = true;
        }
        else
            InputDispatcher::getInstance()->sendEvent(&event);
    }

    return needQuit;
}

void GameApp::pause()
{
    paused = true;
}

void GameApp::unpause()
{
    paused = false;
}

void GameApp::receiveMessage(string msg)
{
    if (msg == GlobalConstants::Paused)
        pause();
    else
        if (msg == GlobalConstants::Resumed)
            unpause();
    else
        std::cout << "Wrong message to GameApp" << std::endl;
}
