/*
 * SceneManager.cpp
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#include "SceneManager.h"
#include <iostream>
#include "../Input/InputDispatcher.h"
using std::cout;
using std::endl;

SceneManager::SceneManager()
: currentScene(nullptr)
{

}


std::shared_ptr<Scene> SceneManager::getCurrentScene()
{
	return currentScene;
}


void SceneManager::addScene(std::shared_ptr<Scene> scene, std::string name)
{
    scenes.emplace(std::make_pair(name, scene));//[name] = scene;
}

void SceneManager::setCurrentScene(std::shared_ptr<Scene>& value)
{
	InputDispatcher::getInstance()->clearHandlers();
    if (currentScene != nullptr )
	{
        currentScene->clear();
	}

	currentScene = value;

    if (currentScene != nullptr)
        currentScene->init(shared_from_this());
    else
        std::cout << "currentScene is NULL" << std::endl;
}

void SceneManager::setCurrentSceneByName(std::string name)
{

    if (currentScene != scenes.at(name))
    {
        std::cout << "Scene name = " << name << std::endl;
        setCurrentScene(scenes.at(name));
    }
}
