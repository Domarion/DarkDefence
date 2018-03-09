#pragma once

#include <string>
#include <map>

#include "Scene.h"

class Scene;

class SceneManager: public std::enable_shared_from_this<SceneManager>
{
public:
    SceneManager() = default;
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
    virtual ~SceneManager() = default;

    std::shared_ptr<Scene> getCurrentScene();
    void addScene(std::shared_ptr<Scene> scene, const std::string& aSceneName);
    void setCurrentSceneByName(std::string name);
    void askForChangeScene(const std::string& aName);
    void clearOldScene();
    void updateCurrentScene(double aTimeStep);
    void renderCurrentScene();

private:
    void setCurrentScene(std::shared_ptr<Scene>& value);

    std::shared_ptr<Scene> currentScene;
    std::map<std::string, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> oldScene;

};

