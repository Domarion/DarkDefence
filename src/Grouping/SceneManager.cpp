/*
 * SceneManager.cpp
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#include "SceneManager.h"
#include "Logging/Logger.h"

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
    if (currentScene )
    {
        currentScene->clear();
    }

    currentScene = value;

    if (currentScene)
    {
        currentScene->init(shared_from_this());
        return;
    }

    LOG_ERROR("Current scene is nullptr.");
}

void SceneManager::setCurrentSceneByName(std::string name)
{
    if (currentScene != scenes.at(name))
    {
        std::string msg = std::string{"SceneName = "} + name;
        LOG_INFO(msg)
        setCurrentScene(scenes.at(name));
    }
}

void SceneManager::askForChangeScene(std::string aName)
{
    if (currentScene != scenes.at(aName))
    {
        oldScene = currentScene;
        oldScene->softClear();
        currentScene = scenes.at(aName);

        if (currentScene != nullptr)
            currentScene->init(shared_from_this());
    }
}

void SceneManager::clearOldScene()
{
    if (oldScene != nullptr)
    {
        oldScene->clear();
        oldScene = nullptr;
    }
}

