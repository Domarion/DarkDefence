/*
 * Scene.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <list>
using std::list;

#include "../GraphicsSystem/CTexture.h"
#include "SceneObject.h"
#include "SceneManager.h"

class SceneObject;
class SceneManager;

class Scene
{
public:
	Scene();
	virtual ~Scene();
	virtual void initScene(SDL_Renderer* renderer, SceneManager* sceneManagerPtr);
	virtual void finalizeScene();
	virtual void loadScene();
	virtual void unloadScene();
	virtual void copyToRender(SDL_Renderer* renderer) const;
	virtual void startUpdate(double timestep);
    virtual void spawnObject(int x, int y, SceneObject* obj);
    SceneObject* findObjectByTag(std::string tag);
    list<SceneObject*>* findObjectsByTag(std::string tag);
protected:
	list<CTexture*> listGUI;
	list<SceneObject*> sceneObjects;
	SDL_Renderer* rendererptr;
	SceneManager* parentSceneManager;
	bool wasInited;

};
