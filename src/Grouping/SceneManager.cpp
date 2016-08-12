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

SceneManager::~SceneManager()
{

	for(auto i = scenes.begin(); i != scenes.end(); ++i)
        delete scenes.at(i->first);

    scenes.clear();

    currentScene = nullptr;
}

Scene* SceneManager::getCurrentScene() const
{
	return currentScene;
}


void SceneManager::addScene(Scene* scene, const string name)
{
	scenes[name] = scene;
}

void SceneManager::setCurrentScene(Scene* value, bool cleanFlag)//TODO:: cleanFlag?
{
	InputDispatcher::getInstance()->clearHandlers();
	if (currentScene != nullptr )//&& cleanFlag)
	{
    //	currentScene->finalizeScene();
        currentScene->resetState();
	}

	currentScene = value;

    if (currentScene != nullptr)
        currentScene->initScene(this);
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
