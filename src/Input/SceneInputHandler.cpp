#include "SceneInputHandler.h"
#include "Scenes/GameScene.h"

bool SceneInputHandler::onClick(Position /*aPoint*/)
{
    return false;
}

bool SceneInputHandler::canDrag() const
{
    return true;
}

bool SceneInputHandler::onDrag(Position aDirection)
{
    if (!mParentScene)
    {
        return false;
    }

    auto gameScene = std::dynamic_pointer_cast<GameScene>(mParentScene);
    if (gameScene && gameScene->getSceneMode() == GameScene::SceneModeT::StandardMode)
    {
        mParentScene->onlyTestMoveCamera(aDirection);
    }

    return false;// не захватываем событие.
}

bool SceneInputHandler::containsPoint(Position) const
{
    return true;
}

void SceneInputHandler::setParentScene(std::shared_ptr<Scene> aParentScene)
{
    mParentScene = aParentScene;
}
