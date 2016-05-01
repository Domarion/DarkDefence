/*
 * GameApp.h
 *
 *  Created on: 9 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <SDL2/SDL.h>
#include "Grouping/SceneManager.h"
class GameApp
{
public:
	GameApp(SceneManager* scmanager, int w = 800, int h = 600);
	~GameApp();
	int GameLoop();
	int renderScene(const Scene* scene);
	void updateScene(Scene* scene, double timestep);
	bool processInput();
	SDL_Renderer* getRenderer();
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Event event;
	SceneManager* sceneManager;
};
