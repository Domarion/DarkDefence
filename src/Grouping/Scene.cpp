/*
 * Scene.cpp
 *
 *  Created on: 8 марта 2016 г.
 *      Author: kostya_hm
 */

#include "Scene.h"
#include "SceneObject.h"
#include "SceneObjectFabric.h"
#include <list>
using std::list;
#include "../Input/InputDispatcher.h"
#include "../GraphicsSystem/newSystem/UIElement/UITextButton.h"
#include "../GlobalScripts/GameModel.h"
#include <iostream>
Scene::Scene(std::shared_ptr<RenderingSystem> &aRenderer, std::shared_ptr<InputDispatcher> aInputDispatcher)
: renderer(aRenderer)
, mInputDispatcher(aInputDispatcher)
, MainRect(std::make_shared<ConcreteComposite>())
, listGUI()
, sceneObjects()
, parentSceneManager(nullptr)
, wasInited(false)
, mCamera(Size(aRenderer->getScreenSize().width, aRenderer->getScreenSize().height))
{
    MainRect->setSize(renderer->getScreenSize());
    MainRect->setPosition(Position(0, 0));
}

void Scene::init(std::shared_ptr<SceneManager> sceneManagerPtr)
{
	parentSceneManager = sceneManagerPtr;
}


Scene::~Scene()
{
}


void Scene::copyToRender() const
{
    for(auto sceneObject : sceneObjects)
        if (sceneObject != nullptr && sceneObject->getSprite() != nullptr )
        {
            Position sceneObjectPosition = sceneObject->getPosition();
            Size sceneObjectSize = sceneObject->getSprite()->getSize();
            if (mCamera.hasIntersection(sceneObjectPosition, sceneObjectSize))
                sceneObject->getSprite()->drawAtPosition(mCamera.worldToCameraPosition(sceneObjectPosition));
        }

    for(const auto& guiItem : listGUI)
        if (guiItem != nullptr)
            guiItem->draw();
}

void Scene::startUpdate(double timestep)
{
    for(auto iter = sceneObjects.begin(); iter != sceneObjects.end(); )
    {

        if ((*iter)->update(timestep) == false)
            sceneObjects.erase(iter++);
        else
            ++iter;
    }
}

void Scene::spawnObject(int x, int y, std::shared_ptr<SceneObject> obj)
{
    if (obj == nullptr)
        return;

    obj->setParentScene(shared_from_this());


    obj->init(x, y);

    auto handler = std::dynamic_pointer_cast<InputHandler>(obj);

    if (handler != nullptr)
        mInputDispatcher->addHandler(handler);

    sceneObjects.push_back(obj);
}

void Scene::destroyObject(std::shared_ptr<SceneObject> obj)
{
    auto handler = std::dynamic_pointer_cast<InputHandler>(obj);

    if (handler != nullptr)
        mInputDispatcher->removeHandler(handler);

    sceneObjects.remove(obj);

    obj->finalize();
}

void Scene::addToUIList(const std::shared_ptr<IComposite> &item)
{
    if (item == nullptr)
        return;

    listGUI.push_back(item);

    auto handler = std::dynamic_pointer_cast<InputHandler>(item);


    if (handler != nullptr)
        mInputDispatcher->addHandler(handler);
    else
        std::cout << "fucking NULL";
}

void Scene::removeFromUIList(const std::shared_ptr<IComposite> &item)
{
    if (item == nullptr)
        return;

    listGUI.remove(item);

    auto handler = std::dynamic_pointer_cast<InputHandler>(item);

    if (handler != nullptr)
        mInputDispatcher->removeHandler(handler);
}

void Scene::addAsInputHandler(std::shared_ptr<InputHandler> item)
{

    if (item != nullptr)
        mInputDispatcher->addHandler(item);
}

void Scene::clearUIList()
{
    MainRect->clearChildren();
    listGUI.clear();
    mInputDispatcher->clearHandlers();
}


std::shared_ptr<SceneObject> Scene::findObjectByTag(std::string tag)
{
    for(auto ptr = sceneObjects.begin(); ptr != sceneObjects.end(); ++ptr)
    {
      if ((*ptr)->getTag() == tag)
          return *ptr;
    }
    return nullptr;
}

Scene::SceneObjectList Scene::findObjectsByTag(string tag)
{
    auto filteredList = std::make_unique<std::list<std::shared_ptr<SceneObject>>>();

    for(auto ptr = sceneObjects.begin(); ptr != sceneObjects.end(); ++ptr)
    {
      if ((*ptr)->getTag() == tag)
        filteredList->push_back(*ptr);
    }

    if (filteredList->empty())
    {
        return nullptr;
    }

    return filteredList;

}

std::shared_ptr<SceneObject> Scene::findObjectWithPos(int x, int y)
{

    SDL_Point point = {x, y};
    for(auto& sceneobject : sceneObjects)
    {
      if (sceneobject != nullptr)
      {
          const SDL_Rect some = {sceneobject->getSprite()->getPosition().x
                                 , sceneobject->getSprite()->getPosition().y
                                , sceneobject->getSprite()->getSize().width
                                , sceneobject->getSprite()->getSize().height
                                };

          if (SDL_PointInRect(&point, &some))
               return sceneobject;
       }
    }
    return nullptr;
}

Scene::SceneObjectList Scene::findObjectsWithPos(int x, int y)
{
    SDL_Point point = {x, y};
    auto filteredList =  std::make_unique<std::list<std::shared_ptr<SceneObject>>>();

    for(auto &sceneobject : sceneObjects)
    {
        if (sceneobject != nullptr)
        {
           const SDL_Rect some = {sceneobject->getSprite()->getPosition().x
                                  , sceneobject->getSprite()->getPosition().y
                                 , sceneobject->getSprite()->getSize().width
                                 , sceneobject->getSprite()->getSize().height
                                 };

           if (SDL_PointInRect(&point, &some))
                filteredList->push_back(sceneobject);
        }
    }

    if (filteredList->empty())
    {
        return nullptr;
    }

    return filteredList;

}

std::shared_ptr<SceneManager> Scene::getParentSceneManager()
{
    return parentSceneManager;
}

void Scene::onGameQuit()
{
    GameModel::getInstance()->saveGameData("GameData/save.bin");

}

std::shared_ptr<ConcreteComposite> &Scene::getMainRect()
{
    return MainRect;
}

std::shared_ptr<RenderingSystem> &Scene::getRenderer()
{
    return renderer;
}

void Scene::addLoadSceneButton(string aButtonName, string aFontName, string aSceneName, int posX, int posY, int width, int height)
{

      auto textButton = std::make_shared<UITextButton>(aButtonName, FontManager::getInstance()->getFontByKind2(aFontName), renderer);
      textButton->setPosition(Position(posX, posY));
      textButton->ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, getParentSceneManager(), aSceneName));

      MainRect->addChild(textButton);

}

void Scene::addSceneButton(string aButtonName,
                           string aFontName,
                           int posX, int posY, int width, int height, std::function<void(string)> handler
                           , std::string aMsg)
{

      auto textButton = std::make_shared<UITextButton>(aButtonName, FontManager::getInstance()->getFontByKind2(aFontName), renderer);
      textButton->setPosition(Position(posX, posY));
      textButton->setMessage(aMsg);
      textButton->ConnectMethod(handler);

      MainRect->addChild(textButton);

}

void Scene::clear()
{
    clearUIList();
    wasInited = false;

    parentSceneManager = nullptr;
}




