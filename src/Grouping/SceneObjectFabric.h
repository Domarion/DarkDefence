#pragma once

#include "SceneObject.h"

class SceneObject;

class SceneObjectFabric
{
public:
    std::unique_ptr<SceneObject> produce(
        string name,
        string tag,
        string spritePath,
        int width,
        int height,
        std::shared_ptr<RenderingSystem>& aRenderingContext);
};

