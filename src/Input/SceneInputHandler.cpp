#include "SceneInputHandler.h"

bool SceneInputHandler::onClick(Position /*aPoint*/)
{
//    if (!mParentScene)
//    {
//        return false;
//    }

//    return mParentScene->findObjectWithPos(aPoint.x, aPoint.y);
    return false;
}

bool SceneInputHandler::canDrag() const
{
    return true;
}

bool SceneInputHandler::onDrag(Position aDirection)
{
    std::cout << "Enter SceneInputHandler::onDrag" << std::endl;

    if (!mParentScene)
    {
        return false;
    }

    std::cout << "SceneInputHandler::onDrag" << std::endl;

    mParentScene->onlyTestMoveCamera(aDirection);

    return true;
}

bool SceneInputHandler::containsPoint(Position) const
{
    return true;
}

void SceneInputHandler::setParentScene(std::shared_ptr<Scene> aParentScene)
{
    mParentScene = aParentScene;
}
