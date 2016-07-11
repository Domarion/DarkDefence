/*
 * SceneObjectFabric.cpp
 *
 *  Created on: 9 апр. 2016 г.
 *      Author: kostya_hm
 */

#include "SceneObjectFabric.h"


SceneObjectFabric::SceneObjectFabric()
{
	// TODO Auto-generated constructor stub

}

SceneObjectFabric::~SceneObjectFabric()
{
	// TODO Auto-generated destructor stub
}

SceneObject* SceneObjectFabric::produce(string name, string tag, string spritePath, int width, int height)
{
    SceneObject* someObject = new SceneObject();

    AnimatedSprite* someSprite = new AnimatedSprite();
    someSprite->setRect(0, 0, width, height);

    someSprite->loadTexture(spritePath);
    someObject->setSprite(someSprite);
    someObject->setName(name);
    someObject->setTag(tag);
    return someObject;
}

void SceneObjectFabric::destroy(SceneObject *toDestroy)
{
    delete toDestroy;
}

