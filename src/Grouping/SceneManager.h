#pragma once

#include <map>
#include <memory>
#include <string>

class Scene;

class SceneManager final
{
public:
    SceneManager() = default;
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
    virtual ~SceneManager() = default;

    const std::shared_ptr<Scene>& getCurrentScene() const;
    void addScene(std::shared_ptr<Scene> scene, const std::string& aSceneName);
    void setCurrentSceneByName(const std::string& aName);
    void askForChangeScene(const std::string& aName);
    void clearOldScene();
    void updateCurrentScene(double aTimeStep);
    void renderCurrentScene();
    void changeScene();

private:
    void setCurrentScene(std::shared_ptr<Scene>& value);

    std::shared_ptr<Scene> currentScene;
    std::map<std::string, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> oldScene;
    std::string mPendingChangeSceneRequest;
};

