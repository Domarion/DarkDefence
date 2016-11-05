/*
 * MainScene.h
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include "../Grouping/Scene.h"

class MainScene: public Scene
{
public:
    MainScene(std::shared_ptr<RenderingSystem> &aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher);
	virtual ~MainScene();
    virtual void init(std::shared_ptr<SceneManager> sceneManagerPtr) override;

private:
    void loadMenuItems(string filename);
    void initUIMenuItems();
    void initBackground();

    vector<pair<string, string> > itemNamesSceneNamesMapping;

};


