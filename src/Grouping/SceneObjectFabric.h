/*
 * SceneObjectFabric.h
 *
 *  Created on: 9 апр. 2016 г.
 *      Author: kostya_hm
 */
#pragma once

#include "SceneObject.h"

class SceneObject;
class SceneObjectFabric
{
public:
	SceneObjectFabric();
    ~SceneObjectFabric();

    std::unique_ptr<SceneObject> produce(string name, string tag, string spritePath, int width, int height, std::shared_ptr<RenderingSystem> &aRenderingContext);
    static void destroy (SceneObject* toDestroy);
};

