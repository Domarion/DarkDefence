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
Scene::Scene(std::shared_ptr<RenderingSystem> &aRenderer)
:renderer(aRenderer)
, MainRect(std::make_shared<ConcreteComposite>())
, listGUI()
, sceneObjects()
, parentSceneManager(nullptr)
, wasInited(false)
{
    MainRect->setSize(renderer->getScreenSize());
    MainRect->setPosition(Position(0, 0));
}

void Scene::init(SceneManager* sceneManagerPtr)
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
            sceneObject->getSprite()->draw();

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

void Scene::spawnObject(int x, int y, SceneObject *obj)
{
    if (obj == nullptr)
        return;

    obj->setParentScene(this);


    obj->init(x, y);


    InputHandler* handler = dynamic_cast<InputHandler*>(obj);

    if (handler != nullptr)
            InputDispatcher::getInstance()->addHandler(handler);

    sceneObjects.push_back(obj);
}

void Scene::destroyObject(SceneObject *obj)
{
    InputHandler* handler = dynamic_cast<InputHandler*>(obj);

    if (handler != nullptr)
            InputDispatcher::getInstance()->removeHandler(handler);

    sceneObjects.remove(obj);

    obj->finalize();
}

void Scene::addToUIList(const std::shared_ptr<IComposite> &item)
{
    if (item == nullptr)
        return;

    listGUI.push_back(item);

    InputHandler* handler = dynamic_cast<InputHandler*>(item.get());


    if (handler != nullptr)
            InputDispatcher::getInstance()->addHandler(handler);
    else
        std::cout << "fucking NULL";
}

void Scene::removeFromUIList(const std::shared_ptr<IComposite> &item)
{
    if (item == nullptr)
        return;

    listGUI.remove(item);

    InputHandler* handler = dynamic_cast<InputHandler*>(item.get());

    if (handler != nullptr)
        InputDispatcher::getInstance()->removeHandler(handler);
}

void Scene::addAsInputHandler(InputHandler *item)
{

    if (item != nullptr)
        InputDispatcher::getInstance()->addHandler(item);
}

void Scene::clearUIList()
{
    MainRect->clearChildren();
    listGUI.clear();

}


SceneObject* Scene::findObjectByTag(std::string tag)
{
    for(auto ptr = sceneObjects.begin(); ptr != sceneObjects.end(); ++ptr)
    {
      if ((*ptr)->getTag() == tag)
          return *ptr;
    }
    return nullptr;
}

list<SceneObject *> *Scene::findObjectsByTag(string tag)
{
    list<SceneObject*>* filteredList =  new list<SceneObject*>();

    for(auto ptr = sceneObjects.begin(); ptr != sceneObjects.end(); ++ptr)
    {
      if ((*ptr)->getTag() == tag)
        filteredList->push_back(*ptr);
    }

    if (filteredList->empty())
    {
        delete filteredList;
        return nullptr;
    }

    return filteredList;

}

SceneObject *Scene::findObjectWithPos(int x, int y)
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

list<SceneObject *> *Scene::findObjectsWithPos(int x, int y)
{
    SDL_Point point = {x, y};
    list<SceneObject*>* filteredList =  new list<SceneObject*>();

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
        delete filteredList;
        return nullptr;
    }

    return filteredList;

}

SceneManager *Scene::getParentSceneManager()
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

void Scene::clear()
{
    if (!sceneObjects.empty())
    {
        for(auto sceneObject : sceneObjects)
            if (sceneObject != nullptr)
                delete sceneObject;
        sceneObjects.clear();
    }


    clearUIList();
    wasInited = false;

    parentSceneManager = nullptr;
}




