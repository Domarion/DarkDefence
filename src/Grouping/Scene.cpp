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

Scene::Scene()
:listGUI(), sceneObjects(), parentSceneManager(nullptr), wasInited(false)
{

	// TODO Auto-generated constructor stub

}

void Scene::initScene(SceneManager* sceneManagerPtr)
{

	parentSceneManager = sceneManagerPtr;

	list<SceneObject*>::const_iterator  const_iter = sceneObjects.begin();
	list<SceneObject*>::const_iterator end = sceneObjects.end();
	for(;const_iter != end; ++const_iter)
        (*const_iter)->init();

}

void Scene::finalizeScene()
{
	list<SceneObject*>::const_iterator  const_iter = sceneObjects.begin();
	list<SceneObject*>::const_iterator end = sceneObjects.end();
	for(;const_iter != end; ++const_iter)
		(*const_iter)->finalize();
	wasInited = true;
}

Scene::~Scene()
{
  //  finalizeScene();
  //  listGUI.clear();
   // sceneObjects.clear();
	// TODO Auto-generated destructor stub
}


void Scene::copyToRender() const
{
	list<CTexture*>::const_iterator  const_iter = listGUI.begin();
	list<CTexture*>::const_iterator end = listGUI.end();
	for(;const_iter != end; ++const_iter)
		(*const_iter)->draw();
}

void Scene::startUpdate(double timestep)
{


    for(auto iter = sceneObjects.begin(); iter != sceneObjects.end(); )
    {

        if ((*iter)->update(timestep) == false)
        {
            sceneObjects.erase(iter++);
           // auto iter2 = sceneObjects.erase(iter++);
           // SceneObjectFabric::destroy(*iter2);
          //  delete *iter2;
        }
        else
            ++iter;
        //if (*iter == nullptr)
          //  --iter;
    }
}

void Scene::spawnObject(int x, int y, SceneObject *obj)
{
    obj->setParentScene(this);

    if (obj->getParentScene() == nullptr)
        std::cout << "WTF WHY NULL" << std::endl;
    else
        std::cout << obj->getName() <<" is NOT NULL"<< std::endl;
    obj->init();
    obj->setPos(x,y);
    if (obj->getSprite() != nullptr)
        obj->getSprite()->setPos(x, y);
    if (obj->getDestructibleObject() != nullptr)
    {
        obj->getDestructibleObject()->setWorldX(x);
        obj->getDestructibleObject()->setWorldY(y);
    }
    sceneObjects.push_back(obj);
}

void Scene::destroyObject(SceneObject *obj)
{
    sceneObjects.remove(obj);
}

void Scene::loadScene()
{

}

void Scene::unloadScene()
{


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
