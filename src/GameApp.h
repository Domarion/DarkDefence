/*
 * GameApp.h
 *
 *  Created on: 9 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "GraphicsSystem/newSystem/RenderingSystem.h"
#include "Grouping/SceneManager.h"

class GameApp
{
public:
    explicit GameApp(std::unique_ptr<SceneManager> aSceneManager, std::unique_ptr<RenderingSystem> aRenderer);
    ~GameApp() = default;
    GameApp(const GameApp&) = delete;
    GameApp& operator=(const GameApp&) = delete;

    void initLibrary(int windowWidth, int windowHeight);
    void addScenes();
    int gameLoop();

    void receiveMessage(string msg);


private:
    void pause();
    void unpause();
    bool processInput();
    void updateScene(std::shared_ptr<Scene> scene, double timestep);
    int renderScene(std::shared_ptr<Scene> scene);
    bool isPaused();
	SDL_Event event;
    std::shared_ptr<RenderingSystem> mRenderer;
    std::shared_ptr<SceneManager> mSceneManager;
    bool paused;
};
