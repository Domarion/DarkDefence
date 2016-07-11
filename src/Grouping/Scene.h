/*
 * Scene.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <list>
using std::list;

#include "../GraphicsSystem/CTexture.h"
#include "SceneObject.h"
#include "SceneManager.h"
#include "../GlobalScripts/Renderer.h"
#include "FontManager.h"

class SceneObject;
class SceneManager;

class Scene
{
public:
	Scene();
	virtual ~Scene();
    virtual void initScene(SceneManager* sceneManagerPtr);
	virtual void finalizeScene();
    virtual void copyToRender() const;
	virtual void startUpdate(double timestep);
    virtual void spawnObject(int x, int y, SceneObject* obj);
    virtual void destroyObject(SceneObject* obj);

    virtual void addToUIList(IDrawable* item);
    virtual void removeFromUIList(IDrawable* item);
    SceneObject* findObjectByTag(std::string tag);
    list<SceneObject*> *findObjectsByTag(std::string tag);
    SceneObject* findObjectWithPos(int x, int y);
    list<SceneObject*>* findObjectsWithPos(int x, int y);

protected:
    list<IDrawable*> listGUI;
    list<SceneObject*> sceneObjects;
	SceneManager* parentSceneManager;
	bool wasInited;

};
