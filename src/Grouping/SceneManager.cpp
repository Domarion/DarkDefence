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
:renderer(nullptr), currentScene(nullptr)
{
	// TODO Auto-generated constructor stub

}

SceneManager::~SceneManager()
{
	// TODO Auto-generated destructor stub
	currentScene = nullptr;
	for(auto i = scenes.begin(); i != scenes.end(); ++i)
		delete scenes[i->first];

        //renderer = nullptr;
}

Scene* SceneManager::getCurrentScene() const
{
	return currentScene;
}



void SceneManager::InitScene()
{


}

void SceneManager::addScene(Scene* scene, const std::string name)
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
		currentScene->finalizeScene();
	}
	currentScene = value;
    currentScene->initScene(this);
}

void SceneManager::setCurrentSceneByName(std::string name)
{

	if (currentScene != scenes[name])
		setCurrentScene(scenes[name]);
	//setCurrentScene(scenes[1]);
}
