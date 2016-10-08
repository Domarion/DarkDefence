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
    explicit GameApp(SceneManager* aSceneManager, std::shared_ptr<RenderingSystem>& aRenderer);
	~GameApp();
    void initLibrary(int windowWidth, int windowHeight);
    int gameLoop();

    void receiveMessage(string msg);


private:
    void pause();
    void unpause();
    bool processInput();
    void updateScene(Scene* scene, double timestep);
    int renderScene(const Scene* scene);
    bool isPaused();
    std::shared_ptr<RenderingSystem> renderer;
	SDL_Event event;
	SceneManager* sceneManager;
    bool paused;
};
