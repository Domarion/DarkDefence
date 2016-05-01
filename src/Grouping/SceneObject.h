/*
 * SceneObject.h
 *
 *  Created on: 13 марта 2016 г.
 *      Author: kostya_hm
 */

#pragma once
#include <string>
using std::string;
#include "../GraphicsSystem/Sprite.h"
#include "Scene.h"
#include "../Mob/DestructibleObject.h"

class Scene;
class SceneObjectFabric;

class SceneObject
{
	friend class SceneObjectFabric;
public:
    virtual void init();
    virtual void setPos(int x, int y);
	virtual void update(double timestep);
	virtual void finalize();
	virtual Sprite * const getSprite() const;
	virtual void setSprite(Sprite* value);
    int getX() const;
    int getY() const;
	//virtual void drawWithCamera(Camera);
    virtual string getName() const;
    virtual void setName(const string &value);

    virtual string getTag() const;
    virtual void setTag(const string &value);
    void setParentScene(Scene* const scene);
    virtual DestructibleObject* getDestructibleObject();
protected:
    SceneObject();
    virtual ~SceneObject();
    Sprite* spriteModel;
    int x, y;
    string name;
    string tag;
    Scene* parentScenePtr;
};
