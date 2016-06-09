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
:currentScene(nullptr)
{

}

SceneManager::~SceneManager()
{

	for(auto i = scenes.begin(); i != scenes.end(); ++i)
		delete scenes[i->first];

    currentScene = nullptr;
}

Scene* SceneManager::getCurrentScene() const
{
	return currentScene;
}


void SceneManager::addScene(Scene* scene, const string name)
{
	scenes[name] = scene;
	if (scenes.size() == 1)
	{

		setCurrentScene(scenes.begin()->second);

	}
}

void SceneManager::setCurrentScene(Scene* value, bool cleanFlag)
{
	InputDispatcher::getInstance()->clearHandlers();
	if (currentScene != nullptr )//&& cleanFlag)
	{
    //	currentScene->finalizeScene();
	}
	currentScene = value;
    if (currentScene == nullptr)
        std::cout << "currentScene is NULL" << std::endl;
    else
        currentScene->initScene(this);
}

void SceneManager::setCurrentSceneByName(std::string name)
{

	if (currentScene != scenes[name])
    {
        std::cout << "Scene name = " << name << std::endl;
		setCurrentScene(scenes[name]);
    }
}
