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
#include <SDL2/SDL_ttf.h>
#include <exception>
#include "Input/InputDispatcher.h"

GameApp::GameApp(SceneManager* scmanager, int w, int h)
:renderer(nullptr), window(nullptr), sceneManager(scmanager)
{


	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
	{
		cout << "SDL_Init Error: " << SDL_GetError() << endl;

	}
	else
	{
		window = SDL_CreateWindow("GameApp", 0, 0, w, h, SDL_WINDOW_SHOWN);

		if (window == nullptr)
			cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (renderer == nullptr)
				cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;


		}
		int imgFlags = IMG_INIT_PNG;
		IMG_Init(imgFlags);
		TTF_Init();
	}

	sceneManager->connectRenderer(getRenderer());
}

GameApp::~GameApp()
{
	if (sceneManager != nullptr)
		delete sceneManager;


	if (renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	if (window != nullptr)
		SDL_DestroyWindow(window);

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

int GameApp::GameLoop()
{



	double lasttime = SDL_GetTicks();
	const double MS_PER_UPDATE = 16.0;//1000ms/60FPS
	double lag = 0.0;
	bool quit = false;
	try
	{
		while(!quit)
		{


			double currenttime = SDL_GetTicks();
			while (SDL_PollEvent(&event) != false)
			{

				if (event.type == SDL_QUIT)
					quit = true;
				else
					InputDispatcher::getInstance()->sendEvent(&event);
					//inputDispatcher->sendEvent(&event);
			}
			double elapsed = currenttime - lasttime;
			lasttime = currenttime;
			lag += elapsed;

			while (lag >= MS_PER_UPDATE)
			{
				updateScene(sceneManager->getCurrentScene(), MS_PER_UPDATE);
				lag -= MS_PER_UPDATE;
			}
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
	//if (scene != nullptr)
	//{
		SDL_RenderClear(renderer);
		if (scene != nullptr)
		{
			scene->copyToRender(renderer);
		}
		else
			cout << "Scene is null!" << endl;
		SDL_RenderPresent(renderer);
	//}

	return 0;
}

void GameApp::updateScene(Scene* scene, double timestep)
{

	if (scene != nullptr)
		scene->startUpdate(timestep);
}

bool GameApp::processInput()
{
	if (SDL_PollEvent(&event) != false)
	{

		if (event.type == SDL_QUIT)
			return false;
		else
			if (event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEBUTTONDOWN)
			InputDispatcher::getInstance()->sendEvent(&event);
			//inputDispatcher->sendEvent(&event);
	}
	return true;
}

SDL_Renderer* GameApp::getRenderer()
{
	return renderer;
}
