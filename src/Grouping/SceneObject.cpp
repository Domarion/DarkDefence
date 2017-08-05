/*
 * SceneObject.cpp
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#include "SceneObject.h"
#include <cassert>
#include "../Logging/Logger.h"

SceneObject::~SceneObject()
{
    finalize();
}

bool SceneObject::isVisible() const
{
    if (!spriteModel)
    {
        LOG_ERROR("No sprite to get visiblity");
        throw std::runtime_error("No sprite to get visiblity");
    }

    return spriteModel->isVisible();
}

void SceneObject::setVisible(bool aVisiblity)
{
    if (!spriteModel)
    {
        LOG_ERROR("No sprite to set visiblity");
        throw std::runtime_error("No sprite to set visiblity");
    }

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

int SceneObject::computeDistanceSqr(std::shared_ptr<SceneObject> second)
{
    if (second  == nullptr)
    {
        LOG_INFO("Cant compare with nullptr SceneObject.");

        return -1;
    }

    return getPosition().ComputeDistanceSqr(second->getPosition());
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

    if (spriteModel)
    {
        spriteModel->setPosition(Position(mX, mY));
    }
}

bool SceneObject::update(double /*timestep*/)
{
    if (spriteModel)
    {
        spriteModel->calculateFrameNumber();
        return true;
    }

    std::string msg = std::string{"SpriteModel is nullptr for "} + getName();
    LOG_ERROR(msg);

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

void SceneObject::setDrawPriority(size_t aPriority)
{
    mDrawPriority = aPriority;
}

size_t SceneObject::getDrawPriority() const
{
    return mDrawPriority;
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
    assert(spriteModel);

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

    if (spriteModel)
    {
        spriteModel->setPosition(aPos);
        return;
    }

    std::string msg = std::string{"SpriteModel is nullptr for "} + getName();
    LOG_ERROR(msg);
}
