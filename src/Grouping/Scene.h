/*
 * Scene.h
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <list>
using std::list;

#include "SceneObject.h"
#include "SceneManager.h"
#include "FontManager.h"
#include "../GraphicsSystem/newSystem/UIElement/ConcreteComposite.h"
#include "../GraphicsSystem/newSystem/Camera2D.h"
#include "../Input/InputDispatcher.h"
#include "../GraphicsSystem/newSystem/StubLayout.h"

class SceneObject;
class SceneManager;

class Scene: public std::enable_shared_from_this<Scene>
{
    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject>>>;

    struct DrawObject
    {
        size_t DrawPriority;
        size_t SceneObjectId;
    };

    friend bool operator<(const Scene::DrawObject& aLeft, const Scene::DrawObject& aRight);

public:
    Scene(std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher);
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    virtual ~Scene() = default;

    virtual void init(std::shared_ptr<SceneManager> sceneManagerPtr);
    virtual void clear();
    virtual void copyToRender() const;
    virtual void startUpdate(double timestep);
    virtual void spawnObject(int x, int y, std::shared_ptr<SceneObject> obj);
    virtual void spawnObject(Position aPos, std::shared_ptr<SceneObject> aObj);

    virtual void destroyObject(std::shared_ptr<SceneObject> obj);

    virtual void addToUIList(const std::shared_ptr<IComposite>& item);
    virtual void removeFromUIList(const std::shared_ptr<IComposite>& item);

    virtual void replaceObject(std::shared_ptr<SceneObject> aObject, std::shared_ptr<SceneObject> aReplacement);
    void softClear();
    void addAsInputHandler(std::shared_ptr<InputHandler> item);
    void clearUIList();
    std::shared_ptr<SceneObject> findObjectByTag(const std::string& aTag);
    SceneObjectList findObjectsByTag(const std::string& aTag);
    std::shared_ptr<SceneObject> findObjectWithPos(int x, int y);
    SceneObjectList findObjectsWithPos(int x, int y);
    SceneObjectList findObjectsInRadius(Position aCenter, size_t aRadius);

    std::shared_ptr<SceneManager> getParentSceneManager();
    virtual void onGameQuit();
    std::shared_ptr<RenderingSystem>& getRenderer();

    std::shared_ptr<ConcreteComposite>& getMainRect();

    void onlyTestMoveCamera(Position aDeltaPosition);

protected:

    mutable std::shared_ptr<RenderingSystem> renderer;
    std::shared_ptr<InputDispatcher> mInputDispatcher;
    std::shared_ptr<ConcreteComposite> MainRect;

    void addLoadSceneButton(string aButtonName, string aFontName, string aSceneName, int posX, int posY, int, int);
    void addSceneButton(string aButtonName, string aFontName, int posX, int posY, int width, int height,
                        std::function<void (string)> handler, const std::string& aMsg);
    void drawSceneObjects() const;
    void drawUI() const;

private:
    void addDrawObject(std::shared_ptr<SceneObject>& aObj);
    void removeDrawObject(size_t aObjId);
    void replaceDrawObject(size_t aOldObjId, std::shared_ptr<SceneObject>& aNewObject);

    list<std::shared_ptr<IComposite> > listGUI;
    list<std::shared_ptr<SceneObject>> sceneObjects;
    std::shared_ptr<SceneManager> parentSceneManager;
    Camera2D mCamera;
    std::list<DrawObject> drawObjects;
};
