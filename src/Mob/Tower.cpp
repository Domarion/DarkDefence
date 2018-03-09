#include "Tower.h"

Tower::Tower(std::shared_ptr<MobModel> model, std::shared_ptr<TileMapManager> aTileMapPtr)
    : Mob(model, aTileMapPtr)
{
}

void Tower::connectMethod(std::function<void(std::shared_ptr<Tower>, int, int)> method)
{
    connectedMethod = method;
}

bool Tower::onClick(Position point)
{
    if (parentScenePtr.expired())
    {
        return false;
    }

    auto sprite = this->getSprite();
    if (!sprite)
    {
        return false;
    }

    auto parentSceneShared = parentScenePtr.lock();

    const auto& camera = parentSceneShared->getCamera();
    if (!camera.hasIntersection(sprite->getRealPosition(), sprite->getSize()))
    {
        return false;
    }

    SDL_Point sPoint{point.x, point.y};
    auto screenPosition = camera.worldToCameraPosition(sprite->getRealPosition());
    SDL_Rect rect = {screenPosition.x, screenPosition.y, sprite->getSize().width, sprite->getSize().height};

    if (!SDL_PointInRect(&sPoint, &rect))
    {
        return false;
    }

    if (connectedMethod != nullptr)
    {
        connectedMethod(std::static_pointer_cast<Tower>(shared_from_this()), point.x, point.y);
    }

    return true;
}



