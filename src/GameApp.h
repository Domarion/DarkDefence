/*
 * GameApp.h
 *
 *  Created on: 9 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "GlobalScripts/Renderer.h"
#include "Grouping/SceneManager.h"

class GameApp
{
public:
    GameApp(SceneManager* aSceneManager);
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
    Renderer* renderer;
    SDL_Window* window;
	SDL_Event event;
	SceneManager* sceneManager;
    bool paused;
};
