#include <cassert>
#include <functional>

#include "Scene.h"
#include "SceneManager.h"
#include "Logging/Logger.h"

const std::shared_ptr<Scene>& SceneManager::getCurrentScene() const
{
    return currentScene;
}

void SceneManager::addScene(std::shared_ptr<Scene> scene, const std::string& aSceneName)
{
    assert(scene && "Scene should be not null in SceneManager");
    scene->bindChangeScene(std::bind(&SceneManager::askForChangeScene, this, std::placeholders::_1));
    scenes.emplace(std::make_pair(aSceneName, scene));
}

void SceneManager::setCurrentScene(std::shared_ptr<Scene>& value)
{
    if (currentScene)
    {
        currentScene->clear();
    }

    currentScene = value;

    if (currentScene)
    {
        currentScene->init();
        return;
    }

    LOG_ERROR("Current scene is nullptr.");
}

void SceneManager::setCurrentSceneByName(const std::string& aName)
{
    if (currentScene != scenes.at(aName))
    {
        std::string msg = std::string{"SceneName = "} + aName;
        LOG_INFO(msg)
        setCurrentScene(scenes.at(aName));
    }
}

void SceneManager::askForChangeScene(const std::string& aName)
{
    if (currentScene != scenes.at(aName))
    {
        mPendingChangeSceneRequest = aName;
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

void SceneManager::updateCurrentScene(double aTimeStep)
{
    if (!currentScene)
    {
        return;
    }

    currentScene->startUpdate(aTimeStep);
}

void SceneManager::renderCurrentScene()
{
    if (!currentScene)
    {
        return;
    }

    currentScene->copyToRender();
}

void SceneManager::changeScene()
{
    if (mPendingChangeSceneRequest.empty())
    {
        return;
    }

    currentScene->softClear();
    currentScene = scenes.at(mPendingChangeSceneRequest);

    assert(currentScene);
    currentScene->init();

    mPendingChangeSceneRequest.clear();
}

