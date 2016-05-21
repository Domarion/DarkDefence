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
    someObject->setName(name);
    someObject->setTag(tag);
   Sprite* someSprite = new Sprite();
    someSprite->setRect(0, 0, width, height);

    someSprite->setTexture(Renderer::getInstance()->loadTextureFromFile(spritePath));


    someObject->setSprite(someSprite);
    someObject->init();

    return someObject;
}

void SceneObjectFabric::destroy(SceneObject *toDestroy)
{
    delete toDestroy;
}

