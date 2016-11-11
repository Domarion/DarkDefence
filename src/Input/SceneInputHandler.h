#pragma once
#include "../Grouping/Scene.h"
#include "InputHandler.h"

class SceneInputHandler: public InputHandler
{
public:
    SceneInputHandler();
    virtual ~SceneInputHandler();
    virtual bool onClick(Position point) override;

    void setParentScene(Scene *value);

private:
    Scene* parentScene;
};

