#include <exception>

#include <SDL_image.h>
#include <SDL_ttf.h>

#include "GlobalConstants.h"
#include "GameApp.h"
#include "Grouping/FontManager.h"
#include "GraphicsSystem/newSystem/RenderingSystem.h"

#include "Scenes/MainScene.h"
#include "Scenes/MapMenuScene.h"
#include "Scenes/GameScene.h"
#include "Scenes/InventoryScene.h"
#include "Scenes/ShopScene.h"
#include "Scenes/ScoreScene.h"

#include "GlobalScripts/ResourceManager.h"
#include "Logging/Logger.h"

GameApp::GameApp(Size aWindowSize)
    : mRenderer(std::make_shared<RenderingSystem>(aWindowSize))
    , mSceneManager()
    , mInputDispatcher(std::make_shared<InputDispatcher>(mRenderer->getScreenSize()))
{
}

void GameApp::preloadData()
{
    // TODO: Dont use singleton in GameModel, move it here and pass to scenes.
    // TODO: Use configuration file instead.
    FontManager::getInstance()->loadFontList("GameData/fontconfig.txt", mRenderer);

    ResourceManager::getInstance()->loadConfigFromFile("GameData/TexturePaths.xml", mRenderer);

    GameModel::getInstance()->getResourcesModel()->loadResourceNamesFromFile("GameData/resourceNames.txt");

    GameModel::getInstance()->loadShopItems("GameData/Items.xml");
    GameModel::getInstance()->loadMissions("GameData/Missions/");

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

    mSceneManager.addScene(std::move(mainScene), "MainScene");
    mSceneManager.addScene(std::move(mapMenuScene), "MapMenuScene");
    mSceneManager.addScene(std::move(gameScene), "GameScene");

    mSceneManager.addScene(std::move(inventoryScene), "InventoryScene");
    mSceneManager.addScene(std::move(shopScene), "ShopScene");
    mSceneManager.addScene(std::move(scoreScene), "ScoreScene");

    mSceneManager.setCurrentSceneByName("MainScene");
}

int GameApp::gameLoop()
{
    int lasttime = SDL_GetTicks();
    const int MS_PER_UPDATE = 16;// 1000 ms / 60 FPS
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
                    mSceneManager.updateCurrentScene(MS_PER_UPDATE);
                    lag -= MS_PER_UPDATE;
                }
            }
            else
            {
                lasttime = currenttime;
            }

            renderScene();
        }
    }
    catch (std::exception& ex)
    {
        LOG_ERROR(ex.what());
        return 1;
    }

    return 0;
}

void GameApp::renderScene()
{
    if (mRenderer == nullptr)
    {
        return;
    }

    mRenderer->renderClear();
    mSceneManager.renderCurrentScene();
    mRenderer->renderPresent();
}

bool GameApp::isPaused()
{
    return mIsPaused;
}

bool GameApp::processInput()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
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

void GameApp::receiveMessage(std::string msg)//TODO: Изменить логику обработки сообщений.
{
    if (msg == GlobalConstants::Paused)
    {
        pause();
    }
    else if (msg == GlobalConstants::Resumed)
    {
        unpause();
    }
    else if (msg == "quit")
    {
        mNeedQuit = true;
    }
    else
    {
        LOG_ERROR("Wrong message to GameApp");
    }
}
