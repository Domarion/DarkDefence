/*
 * main.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "SDL_Engine.h"
#include "GameApp.h"
#include "GraphicsSystem/newSystem/RenderingSystem.h"

int main( int /*argc*/, char** /*args*/)
{

    auto SDL2_Library = std::make_unique<SDL2Engine::SDL2>(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    Size screenSize = SDL2_Library->getScreenResolution();// (800, 480);
    screenSize.height -= 200;//TODO: убрать
    auto renderer = std::make_unique<RenderingSystem>(screenSize);
    auto sceneManager = std::make_unique<SceneManager>();

    auto app = std::make_unique<GameApp>(std::move(sceneManager), std::move(renderer));
    app->preloadData();
    app->addScenes();
    int result = app->gameLoop();

	return result;
}


