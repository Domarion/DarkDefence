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

SceneObject* SceneObjectFabric::produce(string name, string tag, string spritePath, int width, int height,
                                        std::shared_ptr<RenderingSystem>& aRenderingContext)
{
    SceneObject* someObject = new SceneObject();

    auto someSprite = std::make_shared<AnimationSceneSprite>(aRenderingContext);


    someSprite->setSize(Size(width, height));

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

