/*
 * SceneObject.h
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <string>
using std::string;
#include "../GraphicsSystem/UI/AnimatedSprite.h"
#include "Scene.h"
#include "../Mob/DestructibleObject.h"
#include "../AbilitySystem/EffectReceiver.h"
class Scene;
class SceneObjectFabric;


class SceneObject
{
	friend class SceneObjectFabric;
public:
    virtual void init();
    virtual void setPos(int x, int y);
    virtual bool update(double timestep);
	virtual void finalize();
    virtual CTexture * getSprite() const;
    virtual void setSprite(CTexture* value);
    int getX() const;
    int getY() const;
	//virtual void drawWithCamera(Camera);
    virtual string getName() const;
    virtual void setName(const string &value);

    virtual string getTag() const;
    virtual void setTag(const string &value);
    virtual void setParentScene(Scene* scene);
    virtual Scene* getParentScene();
    virtual DestructibleObject* getDestructibleObject();
    virtual EffectReceiver* getEffectReceiver() const;
    virtual ~SceneObject();
protected:
    SceneObject();

   CTexture* spriteModel;
    int x, y;
    string name;
    string tag;
    Scene* parentScenePtr;
};
