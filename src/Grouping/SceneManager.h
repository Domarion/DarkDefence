/*
 * SceneManager.h
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "Scene.h"

#include <string>
using std::string;

#include <map>
using std::map;

class Scene;

class SceneManager: public std::enable_shared_from_this<SceneManager>
{
public:
    SceneManager();
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
    virtual ~SceneManager() = default;

    std::shared_ptr<Scene> getCurrentScene();
    void addScene(std::shared_ptr<Scene> scene, std::string name);
    void setCurrentSceneByName(string name);
    void askForChangeScene(string aName);
    void clearOldScene();
    void updateCurrentScene(double aTimeStep);
    void renderCurrentScene();

private:
    void setCurrentScene(std::shared_ptr<Scene>& value);

    std::shared_ptr<Scene> currentScene;
    map<string, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> oldScene;

};

