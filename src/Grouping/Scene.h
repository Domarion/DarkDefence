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
#include "../GraphicsSystem/newSystem/RenderingSystem.h"
#include "FontManager.h"
#include "../GraphicsSystem/newSystem/UIElement/ConcreteComposite.h"
#include "../GraphicsSystem/newSystem/Camera2D.h"
class SceneObject;
class SceneManager;

class Scene: public std::enable_shared_from_this<Scene>
{
    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject> > >;
public:
    Scene(std::shared_ptr<RenderingSystem>& aRenderer);
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

	virtual ~Scene();
    virtual void init(std::shared_ptr<SceneManager> sceneManagerPtr);
    virtual void clear();
    virtual void copyToRender() const;
	virtual void startUpdate(double timestep);
    virtual void spawnObject(int x, int y, std::shared_ptr<SceneObject> obj);
    virtual void destroyObject(std::shared_ptr<SceneObject> obj);

    virtual void addToUIList(const std::shared_ptr<IComposite> &item);
    virtual void removeFromUIList(const std::shared_ptr<IComposite>& item);

    void addAsInputHandler(InputHandler* item);
    void clearUIList();
    std::shared_ptr<SceneObject> findObjectByTag(std::string tag);
    SceneObjectList findObjectsByTag(std::string tag);
    std::shared_ptr<SceneObject> findObjectWithPos(int x, int y);
    SceneObjectList findObjectsWithPos(int x, int y);
    std::shared_ptr<SceneManager> getParentSceneManager();
    virtual void onGameQuit();
    std::shared_ptr<RenderingSystem>& getRenderer();

    std::shared_ptr<ConcreteComposite>& getMainRect();

protected:
    mutable std::shared_ptr<RenderingSystem> renderer;
    std::shared_ptr<ConcreteComposite> MainRect;

     void addLoadSceneButton(string aButtonName, string aFontName, string aSceneName, int posX, int posY, int width, int height);

private:


    list<std::shared_ptr<IComposite> > listGUI;
    list<std::shared_ptr<SceneObject>> sceneObjects;
    std::shared_ptr<SceneManager> parentSceneManager;
    bool wasInited;
    Camera2D mCamera;
};
