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
#include "Grouping/FontManager.h"
#include "GlobalConstants.h"

#include "Scenes/MainScene.h"
#include "Scenes/MapMenuScene.h"
#include "Scenes/GameScene.h"
#include "Scenes/InventoryScene.h"
#include "Scenes/ShopScene.h"
#include "Scenes/ScoreScene.h"
#include <string>
#include "GlobalScripts/ResourceManager.h"

GameApp::GameApp(std::unique_ptr<SceneManager> aSceneManager, std::unique_ptr<RenderingSystem>&& aRenderer)
    : mRenderer(std::move(aRenderer))
    , mSceneManager(std::move(aSceneManager))
    , mInputDispatcher(std::make_shared<InputDispatcher>(mRenderer->getScreenSize()))
    , mIsPaused(false)
    , mNeedQuit(false)
{
}

void GameApp::preloadData()
{
    FontManager::getInstance()->loadFontList("GameData/fontconfig.txt", mRenderer);

    ResourceManager::getInstance()->loadConfigFromFile("GameData/TexturePaths.xml", mRenderer);

    GameModel::getInstance()->getResourcesModel()->loadResourceNamesFromFile("GameData/resourceNames.txt");

    GameModel::getInstance()->loadShopItems("GameData/Items.xml");

    GameModel::getInstance()->loadGameData("GameData/save.bin");
}

void GameApp::addScenes()
{
    auto mainScene = std::make_unique<MainScene>(mRenderer, mInputDispatcher);
    auto mapMenuScene = std::make_unique<MapMenuScene>(mRenderer, mInputDispatcher);
    auto gameScene = std::make_unique<GameScene>(mRenderer, mInputDispatcher);
    auto inventoryScene = std::make_unique<InventoryScene>(mRenderer, mInputDispatcher);
    auto shopScene = std::make_unique<ShopScene>(mRenderer, mInputDispatcher);
    auto scoreScene = std::make_unique<ScoreScene>(mRenderer, mInputDispatcher);

    mainScene->ConnectMethod(std::bind(&GameApp::receiveMessage, this, std::placeholders::_1));

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
                    //TODO: Вынести в SceneManager
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
        std::cerr << "Exception: " << ex.what() << std::endl;
        return 1;
    }

	return 0;
}

void GameApp::renderScene(std::shared_ptr<Scene> scene)
{
    if (mRenderer == nullptr || scene == nullptr)
    {
        return;
    }

    mRenderer->renderClear();
    scene->copyToRender();
    mRenderer->renderPresent();
}

bool GameApp::isPaused()
{
    return mIsPaused;
}

void GameApp::updateScene(std::shared_ptr<Scene> scene, double timestep)
{
    if (scene != nullptr)
    {
        scene->startUpdate(timestep);
        mSceneManager->clearOldScene();
    }
}

bool GameApp::processInput()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_KEYDOWN) //TestOnly
        {
            Position deltaPos{};
            if (event.key.keysym.sym == SDLK_LEFT)
                deltaPos.x = -50;
            else if (event.key.keysym.sym == SDLK_RIGHT)
                deltaPos.x = +50;

            mSceneManager->getCurrentScene()->onlyTestMoveCamera(deltaPos);
        }
        else if (event.type == SDL_QUIT)
        {
            mNeedQuit = true;
        }
        else
        {
            mInputDispatcher->sendEvent(event);
        }
    }

    return mNeedQuit;
}

void GameApp::pause()
{
    mIsPaused = true;
}

void GameApp::unpause()
{
    mIsPaused = false;
}

void GameApp::receiveMessage(string msg)//TODO: Изменить логику обработки сообщений.
{
    if (msg == GlobalConstants::Paused)
    {
        pause();
    }
    else
        if (msg == GlobalConstants::Resumed)
        {
            unpause();
        }
        else
            if (msg == "quit")
            {
                mNeedQuit = true;
            }
            else
            {
                std::cout << "Wrong message to GameApp" << std::endl;
            }
}
