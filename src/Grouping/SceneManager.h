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
//#include <vector>
//using std::vector;
#include <map>
using std::map;

class Scene;

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();
	Scene* getCurrentScene() const;
	void setCurrentScene(Scene* value, bool cleanFlag = false);
	void addScene(Scene* scene, const string name);
	void addSceneByName(string name);
	void removeScene(string name);

	void setCurrentSceneByName(string name);
private:
	SDL_Renderer* renderer;
	Scene* currentScene;

	map<string, Scene*> scenes;
	void InitScene();
};

