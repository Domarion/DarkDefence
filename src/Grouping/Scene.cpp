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



Scene::Scene()
:listGUI(), sceneObjects(), parentSceneManager(nullptr), wasInited(false)
{

	// TODO Auto-generated constructor stub

}

void Scene::initScene(SceneManager* sceneManagerPtr)
{

	parentSceneManager = sceneManagerPtr;

    /*list<SceneObject*>::const_iterator  const_iter = sceneObjects.begin();
	list<SceneObject*>::const_iterator end = sceneObjects.end();
	for(;const_iter != end; ++const_iter)
        (*const_iter)->init();
*/
}

void Scene::finalizeScene()
{

    list<SceneObject*>::iterator  iter1 = sceneObjects.begin();
    list<SceneObject*>::iterator end = sceneObjects.end();
    for(;iter1 != end; ++iter1)
        delete (*iter1);


    list<IDrawable*>::iterator  iter2 = listGUI.begin();
    list<IDrawable*>::iterator end2 = listGUI.end();
    for(;iter2 != end2; ++iter2)
        delete (*iter2);

	wasInited = true;

    parentSceneManager = nullptr;
}

Scene::~Scene()
{
    finalizeScene();
}


void Scene::copyToRender() const
{
    list<IDrawable*>::const_iterator  const_iter = listGUI.begin();
    list<IDrawable*>::const_iterator end = listGUI.end();
	for(;const_iter != end; ++const_iter)
		(*const_iter)->draw();
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
   // obj->setPos(x,y);

   // if (obj->getSprite() != nullptr)
    //    obj->getSprite()->setPos(x, y);



    /*if (obj->getDestructibleObject() != nullptr)
    {
        obj->getDestructibleObject()->setWorldX(x);
        obj->getDestructibleObject()->setWorldY(y);
    }*/

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
}

void Scene::removeFromUIList(IDrawable *item)
{
    if (item == nullptr)
        return;

    listGUI.remove(item);
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

list<SceneObject *> &Scene::findObjectsByTag(string tag)
{
    list<SceneObject*>* filteredList =  new list<SceneObject*>();

    for(auto ptr = sceneObjects.begin(); ptr != sceneObjects.end(); ++ptr)
    {
      if ((*ptr)->getTag() == tag)
        filteredList->push_back(*ptr);
    }

   /* if (filteredList->empty())
    {
        delete filteredList;
        return nullptr;
    }*/
    return *filteredList;

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
