/*
 * SceneObject.cpp
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#include "SceneObject.h"

SceneObject::SceneObject()
:spriteModel(new Sprite())
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

void SceneObject::setParentScene(Scene* const scene)
{
    parentScenePtr = scene;
}

DestructibleObject *SceneObject::getDestructibleObject()
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
        spriteModel->getRect()->x = x;
         spriteModel->getRect()->y = y;
    }

}

void SceneObject::update(double timestep)
{
}

void SceneObject::init()
{
}

void SceneObject::finalize()
{
     //delete spriteModel;
}

Sprite* const SceneObject::getSprite() const
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
