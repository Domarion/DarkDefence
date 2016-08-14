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

GameApp::GameApp(SceneManager* aSceneManager)
:renderer(nullptr), window(nullptr), sceneManager(aSceneManager), paused(false)
{

}

GameApp::~GameApp()
{
    if (sceneManager != nullptr)
        delete sceneManager;

    renderer->destroyRenderer();
    renderer = nullptr;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void GameApp::initLibrary(int windowWidth, int windowHeight)
{
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0)
    {
        renderer = Renderer::getInstance();
        renderer->initRenderer(windowWidth, windowHeight);

        int imgFlags = IMG_INIT_PNG;
        IMG_Init(imgFlags);
        TTF_Init();

        FontManager::getInstance()->loadFontList("GameData/fontconfig.txt");
    }
    else
    {
       cout << "SDL_Init Error: " << SDL_GetError() << endl;
    }
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
                    updateScene(sceneManager->getCurrentScene(), MS_PER_UPDATE);
                    lag -= MS_PER_UPDATE;
                }
            }
            else
                lasttime = currenttime;

            renderScene(const_cast<const Scene*>(sceneManager->getCurrentScene()));
        }
    }
    catch (std::exception &ex)
    {
        cout << "Exception: " << ex.what() << endl;
        return 1;
    }

	return 0;
}

int GameApp::renderScene(const Scene* scene)
{
    if (renderer != nullptr)
    {

        renderer->renderClear();

        if (scene != nullptr)
        {
            scene->copyToRender();
        }
        else
            cout << "Scene is null!" << endl;

        renderer->renderPresent();

    }

    return 0;
}

bool GameApp::isPaused()
{
    return paused;
}

void GameApp::updateScene(Scene* scene, double timestep)
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
            needQuit = true;
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
