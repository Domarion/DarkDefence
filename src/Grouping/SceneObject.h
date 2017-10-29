/*
 * SceneObject.h
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "../GraphicsSystem/newSystem/ConcreteUIViews/AnimationSceneSprite.h"
#include "Scene.h"
#include "../Mob/DestructibleObject.h"
#include "../AbilitySystem/EffectReceiver.h"
#include "../Input/InputHandler.h"

using std::string;

class Scene;


class SceneObject
{
public:
    SceneObject() = default;
    virtual ~SceneObject();

    virtual void init(int x, int y);
    virtual void setPos(int x, int y);
    virtual bool update(double timestep);
	virtual void finalize();
    virtual const std::shared_ptr<AnimationSceneSprite>& getSprite() const;
    virtual void setSprite(std::shared_ptr<AnimationSceneSprite> &value);

    int getX() const;
    int getY() const;
    Position getPosition() const;
    Position getRealPosition() const;

    void setPos(SDL_Point aPos);
    void setPosition(Position aPos);

    virtual string getName() const;
    virtual void setName(const string &value);

    virtual string getTag() const;
    virtual void setTag(const string& value);
    virtual void setParentScene(std::shared_ptr<Scene> scene);
    virtual std::shared_ptr<Scene> getParentScene();
    virtual std::shared_ptr<DestructibleObject> getDestructibleObject() const;
    virtual std::shared_ptr<EffectReceiver> getEffectReceiver() const;
    virtual std::shared_ptr<InputHandler> getInputHandler() const;
    virtual void setInputHandler(std::shared_ptr<InputHandler> aInputHandler);

    int computeDistanceSqr(std::shared_ptr<SceneObject> second);
    bool isVisible() const;
    void setVisible(bool aVisiblity);

    std::shared_ptr<AnimationSceneSprite> getModifiableSprite() const;

    void setDrawPriority(size_t aPriority);
    size_t getDrawPriority() const;
    size_t getId() const;
    static void resetSceneObjectIds();
protected:

    static size_t sceneObjectCurrentId;

    std::shared_ptr<AnimationSceneSprite> spriteModel;
    int mX{0}, mY{0};
    string name;
    string tag;
    std::weak_ptr<Scene> parentScenePtr;
    std::shared_ptr<InputHandler> mInputHandler;
    size_t mDrawPriority = 0;
    size_t mSceneObjectId = ++sceneObjectCurrentId;

};
