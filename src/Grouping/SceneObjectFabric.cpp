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

std::unique_ptr<SceneObject> SceneObjectFabric::produce(string name, string tag, string spritePath, int width, int height,
                                        std::shared_ptr<RenderingSystem>& aRenderingContext)
{
    auto someObject = std::make_unique<SceneObject>();
    auto someSprite = std::make_shared<AnimationSceneSprite>(aRenderingContext);



    someSprite->loadTexture(spritePath);


    if (width == 0 && height == 0)
    {
        someSprite->setSizeFromTexture();
    }
    else
    {
        someSprite->setSize(Size(width, height));
    }

    someObject->setSprite(someSprite);
    someObject->setName(name);
    someObject->setTag(tag);

    return someObject;
}

void SceneObjectFabric::destroy(SceneObject *toDestroy)
{
    delete toDestroy;
}

