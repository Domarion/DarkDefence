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

    SceneObject* const produce(string name, string tag, SDL_Renderer* renderer, string spritePath, int width, int height);
};

