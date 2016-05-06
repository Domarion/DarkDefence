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
    virtual void initScene(SceneManager* sceneManagerPtr);
	virtual void finalizeScene();
	virtual void loadScene();
	virtual void unloadScene();
    virtual void copyToRender() const;
	virtual void startUpdate(double timestep);
    virtual void spawnObject(int x, int y, SceneObject* obj);
    virtual void destroyObject(SceneObject* obj);
    SceneObject* findObjectByTag(std::string tag);
    list<SceneObject*>* findObjectsByTag(std::string tag);
    SceneObject* findObjectWithPos(int x, int y);
    list<SceneObject*>* findObjectsWithPos(int x, int y);

protected:
	list<CTexture*> listGUI;
	list<SceneObject*> sceneObjects;
	SceneManager* parentSceneManager;
	bool wasInited;

};
