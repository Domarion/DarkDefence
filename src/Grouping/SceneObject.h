/*
 * SceneObject.h
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <string>
using std::string;
#include "../GraphicsSystem/newSystem/ConcreteUIViews/AnimationSceneSprite.h"
#include "Scene.h"
#include "../Mob/DestructibleObject.h"
#include "../AbilitySystem/EffectReceiver.h"
class Scene;


class SceneObject
{
public:
    SceneObject();

    virtual void init(int x, int y);
    virtual void setPos(int x, int y);
    virtual bool update(double timestep);
	virtual void finalize();
    virtual const std::shared_ptr<AnimationSceneSprite> &getSprite() const;
    virtual void setSprite(std::shared_ptr<AnimationSceneSprite> &value);
    int getX() const;
    int getY() const;
    SDL_Point getPos() const;
    Position getPosition() const;
    void setPos(SDL_Point aPos);

    virtual string getName() const;
    virtual void setName(const string &value);

    virtual string getTag() const;
    virtual void setTag(const string &value);
    virtual void setParentScene(std::shared_ptr<Scene> scene);
    virtual std::shared_ptr<Scene> getParentScene();
    virtual std::shared_ptr<DestructibleObject> getDestructibleObject() const;
    virtual std::shared_ptr<EffectReceiver> getEffectReceiver() const;

    int computeDistanceSqr(int x0, int y0, int x1, int y1);
    int computeDistanceSqr(std::shared_ptr<SceneObject> second);
    virtual ~SceneObject();
    bool isVisible() const;
    void setVisible(bool aVisiblity);

//    void setX(int value);

//    void setY(int value);

protected:


    std::shared_ptr<AnimationSceneSprite> spriteModel;
    int x, y;
    string name;
    string tag;
    std::weak_ptr<Scene> parentScenePtr;
};
