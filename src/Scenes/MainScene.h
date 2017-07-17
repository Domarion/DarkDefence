/*
 * MainScene.h
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "../Grouping/Scene.h"
#include <functional>

class MainScene: public Scene
{
public:

    MainScene(std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher);
    virtual ~MainScene();
    virtual void init(std::shared_ptr<SceneManager> sceneManagerPtr) override;
    void ConnectMethod(std::function<void(string)> handler);

private:

    void loadMenuItems(string filename);
    void initUIMenuItems();
    void initBackground();

    vector<pair<string, string> > itemNamesSceneNamesMapping;
    std::function<void(string)> method;
};


