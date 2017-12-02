/*
 * GameApp.h
 *
 *  Created on: 9 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "GraphicsSystem/newSystem/RenderingSystem.h"
#include "Grouping/SceneManager.h"
#include "Input/InputDispatcher.h"

class GameApp final
{
public:

    explicit GameApp(std::unique_ptr<SceneManager>&& aSceneManager, std::unique_ptr<RenderingSystem>&& aRenderer);
    ~GameApp() = default;

    GameApp(const GameApp&) = delete;
    GameApp& operator=(const GameApp&) = delete;

    void initLibrary(int windowWidth, int windowHeight);
    void preloadData();
    void addScenes();
    int gameLoop();

    void receiveMessage(string msg);

private:

    void pause();
    void unpause();
    bool processInput();
    void renderScene();
    bool isPaused();
    SDL_Event event;
    std::shared_ptr<RenderingSystem> mRenderer;
    std::shared_ptr<SceneManager> mSceneManager;
    std::shared_ptr<InputDispatcher> mInputDispatcher;
    bool mIsPaused = false;
    bool mNeedQuit = false;
};
