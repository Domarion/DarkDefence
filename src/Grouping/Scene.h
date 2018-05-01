#pragma once

#include <functional>
#include <list>

#include "SceneObject.h"
#include "FontManager.h"
#include "../GraphicsSystem/newSystem/UIElement/ConcreteComposite.h"
#include "../GraphicsSystem/newSystem/Camera2D.h"
#include "../Input/InputDispatcher.h"
#include "../GraphicsSystem/newSystem/StubLayout.h"

class SceneObject;

class Scene: public std::enable_shared_from_this<Scene>
{
    using SceneObjectList = std::unique_ptr<std::list<std::shared_ptr<SceneObject>>>;
    using ChangeSceneFunction = std::function<void(const std::string&)>;
    struct DrawObject
    {
        size_t DrawPriority = 0;
        size_t SceneObjectId = 0;
    };

    friend bool operator<(const Scene::DrawObject& aLeft, const Scene::DrawObject& aRight);

public:
    Scene(std::shared_ptr<RenderingSystem>& aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher);
    Scene(const Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    virtual ~Scene() = default;

    virtual void init();
    virtual void clear();
    virtual void copyToRender() const;
    virtual void startUpdate(double timestep);
    virtual void spawnObject(Position aPos, std::shared_ptr<SceneObject> aObj);

    virtual void destroyObject(std::shared_ptr<SceneObject> obj);

    virtual void addToUIList(const std::shared_ptr<IComposite>& item);
    virtual void removeFromUIList(const std::shared_ptr<IComposite>& item);

    virtual void replaceObject(std::shared_ptr<SceneObject> aObject, std::shared_ptr<SceneObject> aReplacement);

    void bindChangeScene(const ChangeSceneFunction& aChangeSceneCallback);

    void askForChangeScene(const std::string& aName);
    void softClear();
    void addAsInputHandler(std::shared_ptr<InputHandler> item);
    void clearUIList();
    std::shared_ptr<SceneObject> findObjectByTag(const std::string& aTag);
    SceneObjectList findObjectsByTag(const std::string& aTag);
    std::shared_ptr<SceneObject> findObjectWithPos(int x, int y);
    SceneObjectList findObjectsWithPos(int x, int y);
    SceneObjectList findObjectsInRadius(Position aCenter, size_t aRadius);

    virtual void onGameQuit();
    std::shared_ptr<RenderingSystem>& getRenderer();

    std::shared_ptr<ConcreteComposite>& getMainRect();

    void onlyTestMoveCamera(Position aDeltaPosition);

    Camera2D getCamera() const;
protected:

    mutable std::shared_ptr<RenderingSystem> renderer;
    std::shared_ptr<InputDispatcher> mInputDispatcher;
    std::shared_ptr<ConcreteComposite> MainRect;

    void addLoadSceneButton(
        const std::string& aButtonName,
        const std::string& aFontName,
        const std::string& aSceneName,
        int posX,
        int posY,
        int,
        int);
    void addSceneButton(
        const std::string& aButtonName,
        const std::string& aFontName,
        int posX,
        int posY,
        int width,
        int height,
        std::function<void (std::string)> handler,
        const std::string& aMsg);
    void drawSceneObjects() const;
    void drawUI() const;

private:
    void addDrawObject(std::shared_ptr<SceneObject>& aObj);
    void removeDrawObject(size_t aObjId);
    void replaceDrawObject(size_t aOldObjId, std::shared_ptr<SceneObject>& aNewObject);

    std::list<std::shared_ptr<IComposite>> listGUI;
    std::list<std::shared_ptr<SceneObject>> sceneObjects;
    Camera2D mCamera;
    std::list<DrawObject> drawObjects;
    ChangeSceneFunction mChangeSceneCallback;
};
