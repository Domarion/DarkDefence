/*
 * SceneObject.cpp
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#include "SceneObject.h"
#include <cassert>

SceneObject::~SceneObject()
{
    finalize();
}

bool SceneObject::isVisible() const
{
    if (spriteModel == nullptr)
        throw std::runtime_error("No sprite to get visiblity");

    return spriteModel->isVisible();
}

void SceneObject::setVisible(bool aVisiblity)
{
    if (spriteModel == nullptr)
        throw std::runtime_error("No sprite to set visiblity");
    spriteModel->setVisible(aVisiblity);
}

string SceneObject::getTag() const
{
    return tag;
}

void SceneObject::setTag(const string &value)
{
    tag = value;
}

void SceneObject::setParentScene(std::shared_ptr<Scene> scene)
{
    parentScenePtr = scene;
}

std::shared_ptr<Scene> SceneObject::getParentScene()
{
    return parentScenePtr.lock();
}

std::shared_ptr<DestructibleObject> SceneObject::getDestructibleObject() const
{
    return nullptr;
}

std::shared_ptr<EffectReceiver>  SceneObject::getEffectReceiver() const
{
    return nullptr;
}

std::shared_ptr<InputHandler> SceneObject::getInputHandler() const
{
    return mInputHandler;
}

void SceneObject::setInputHandler(std::shared_ptr<InputHandler> aInputHandler)
{
    mInputHandler = aInputHandler;
}

int SceneObject::computeDistanceSqr(int x0, int y0, int x1, int y1)
{
    int xdist = x0 - x1;
    int ydist = y0 - y1;

    return (xdist*xdist + ydist*ydist);
}

int SceneObject::computeDistanceSqr(std::shared_ptr<SceneObject> second)
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
    mX = x;
    mY = y;
    if (spriteModel != nullptr)
    {
        spriteModel->setPosition(Position(mX, mY));
    }

}

bool SceneObject::update(double /*timestep*/)
{
    if (spriteModel != nullptr)
        spriteModel->calculateFrameNumber();
    return true;
}




void SceneObject::finalize()
{
}

const std::shared_ptr<AnimationSceneSprite> &SceneObject::getSprite() const
{
	return spriteModel;
}

std::shared_ptr<AnimationSceneSprite> SceneObject::getModifiableSprite() const
{
    return spriteModel;
}

void SceneObject::setSprite(std::shared_ptr<AnimationSceneSprite> & value)
{
    spriteModel = value;
}

int SceneObject::getX() const
{
    return mX;
}

int SceneObject::getY() const
{
    return mY;
}

Position SceneObject::getPosition() const
{
    return Position(getX(), getY());
}

Position SceneObject::getRealPosition() const
{
    assert(spriteModel != nullptr);
    return spriteModel->getRealPosition();
}

void SceneObject::setPos(SDL_Point aPos)
{
    setPos(aPos.x, aPos.y);
}

void SceneObject::setPosition(Position aPos)
{
    mX = aPos.x;
    mY = aPos.y;

    if (spriteModel != nullptr)
    {
        spriteModel->setPosition(aPos);
    }
}
