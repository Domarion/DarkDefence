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
#include "../GraphicsSystem/UI/TextButton.h"

Scene::Scene()
:listGUI(), sceneObjects(), parentSceneManager(nullptr), wasInited(false)
{
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

    for(auto guiItem : listGUI)
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

void Scene::addToUIList(IDrawable *item)
{
    if (item == nullptr)
        return;

    listGUI.push_back(item);

    InputHandler* handler = dynamic_cast<InputHandler*>(item);

    if (handler != nullptr)
            InputDispatcher::getInstance()->addHandler(handler);
}

void Scene::removeFromUIList(IDrawable *item)
{
    if (item == nullptr)
        return;

    listGUI.remove(item);

    InputHandler* handler = dynamic_cast<InputHandler*>(item);

    if (handler != nullptr)
        InputDispatcher::getInstance()->removeHandler(handler);
}

void Scene::clearUIList()
{
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
    for(auto ptr = sceneObjects.begin(); ptr != sceneObjects.end(); ++ptr)
    {
      if ((*ptr) != nullptr)
      {
          const SDL_Rect some = (*ptr)->getSprite()->getRect();
         if (SDL_PointInRect(&point, &some))
            return *ptr;
       }
    }
    return nullptr;
}

list<SceneObject *> *Scene::findObjectsWithPos(int x, int y)
{
    SDL_Point point = {x, y};
    list<SceneObject*>* filteredList =  new list<SceneObject*>();

    for(auto ptr = sceneObjects.begin(); ptr != sceneObjects.end(); ++ptr)
    {
        if ((*ptr) != nullptr)
        {
           const SDL_Rect some = (*ptr)->getSprite()->getRect();

           if (SDL_PointInRect(&point, &some))
                filteredList->push_back(*ptr);
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

void Scene::addLoadSceneButton(string aButtonName, string aFontName, string aSceneName, int posX, int posY, int width, int height)
{
    TextButton* button = new TextButton();
    button->setFont(FontManager::getInstance()->getFontByKind(aFontName));
    button->setRect(posX, posY, width, height);
    button->setText(aButtonName);
    button->ConnectMethod(std::bind(&SceneManager::setCurrentSceneByName, getParentSceneManager(), aSceneName));
    addToUIList(button);
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


    for(auto guiItem : listGUI)
        if (guiItem != nullptr)
            delete guiItem;

    listGUI.clear();

    wasInited = false;

    parentSceneManager = nullptr;
}




