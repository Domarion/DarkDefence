#include "SceneInputHandler.h"

SceneInputHandler::SceneInputHandler()
    :parentScene(nullptr)
{

}

SceneInputHandler::~SceneInputHandler()
{

}

bool SceneInputHandler::onClick(Position point)
{
    if (parentScene == nullptr)
        return false;

    return (parentScene->findObjectWithPos(point.x, point.y)) != nullptr;
}

void SceneInputHandler::setParentScene(Scene *value)
{
    parentScene = value;
}
