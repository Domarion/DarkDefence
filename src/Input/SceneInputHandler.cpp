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

    if (abs(aDirection.x) < 7 && abs(aDirection.y) < 7)
    {
        // Should not move camera if touched screen slightly
        return false;
    }

    auto gameScene = std::dynamic_pointer_cast<GameScene>(mParentScene);
    if (gameScene && gameScene->getSceneMode() == GameScene::SceneModeT::StandardMode)
    {
        auto& renderer = mParentScene->getRenderer();
        auto& tilemap = gameScene->getTileMap();
        if (!renderer || !tilemap.isInitialized())
        {
            return false;
        }
        Size screenSize = renderer->getScreenSize();

        Size mapSize = tilemap.getMapSize();

        if (screenSize == mapSize)
        {
            return false;
        }
        mParentScene->onlyTestMoveCamera(aDirection);
        return true;
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
