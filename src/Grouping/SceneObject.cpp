/*
 * SceneObject.cpp
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#include "SceneObject.h"

SceneObject::SceneObject()
:spriteModel(nullptr), x(0), y(0), parentScenePtr(nullptr)
{
	// TODO Auto-generated constructor stub

}

//void SceneObject::setY(int value)
//{
//    y = value;
//    if (spriteModel != nullptr)
//        spriteModel->setPosY(y);
//}

//void SceneObject::setX(int value)
//{
//    x = value;
//    if (spriteModel != nullptr)
//        spriteModel->setPosX(x);
//}


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

int SceneObject::computeDistanceSqr(int x0, int y0, int x1, int y1)
{
    int xdist = x0 - x1;
    int ydist = y0 - y1;

    return (xdist*xdist + ydist*ydist);
}

int SceneObject::computeDistanceSqr(SceneObject *second)
{
    if (second  == nullptr)
        return -1;

    return computeDistanceSqr(getX(), getY(), second->getX(), second->getY());
}

string SceneObject::getName() const
{
    return name;
}

void SceneObject::setName(const string &value)
{
    name = value;
}

void SceneObject::init(int x, int y)
{
    setPos(x, y);
}

void SceneObject::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
    if (spriteModel != nullptr)
    {
        spriteModel->setPosition(Position(x, y));
    }

}

bool SceneObject::update(double timestep)
{
    if (spriteModel != nullptr)
        spriteModel->calculateFrameNumber();
    return true;
}




void SceneObject::finalize()
{
    parentScenePtr = nullptr;
}

const std::shared_ptr<AnimationSceneSprite> &SceneObject::getSprite() const
{
	return spriteModel;
}

void SceneObject::setSprite(std::shared_ptr<AnimationSceneSprite> & value)
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

SDL_Point SceneObject::getPos() const
{
   SDL_Point currentPos = { getX(), getY()};
   return currentPos;
}

Position SceneObject::getPosition() const
{
    return Position(getX(), getY());
}

void SceneObject::setPos(SDL_Point aPos)
{
    setPos(aPos.x, aPos.y);
}
