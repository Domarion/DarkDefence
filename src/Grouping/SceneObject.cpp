/*
 * SceneObject.cpp
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#include "SceneObject.h"

SceneObject::SceneObject()
:spriteModel(nullptr)
{
	// TODO Auto-generated constructor stub

}

SceneObject::~SceneObject()
{
finalize();
	// TODO Auto-generated destructor stub
}

string SceneObject::getTag() const
{
    return tag;
}

void SceneObject::setTag(const string &value)
{
    tag = value;
}

void SceneObject::setParentScene(Scene* scene)
{
    parentScenePtr = scene;
}

Scene *SceneObject::getParentScene()
{
    return parentScenePtr;
}

DestructibleObject *SceneObject::getDestructibleObject()
{
    return nullptr;
}

EffectReceiver *SceneObject::getEffectReceiver() const
{
    return nullptr;
}

string SceneObject::getName() const
{
    return name;
}

void SceneObject::setName(const string &value)
{
    name = value;
}

void SceneObject::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
    if (spriteModel != nullptr)
    {
        spriteModel->setPos(x, y);
    }

}

bool SceneObject::update(double timestep)
{
    return true;
}


void SceneObject::init()
{
   // spriteModel = new Sprite();
}

void SceneObject::finalize()
{
     delete spriteModel;
}

Sprite* SceneObject::getSprite() const
{
	return spriteModel;
}

void SceneObject::setSprite(Sprite* value)
{
    spriteModel = value;
}
int SceneObject::getX() const
{
    return x;
}
int SceneObject::getY() const
{
    return y;
}
