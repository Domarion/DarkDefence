#include "ResourcePlace.h"
#include "../GlobalScripts/GameModel.h"
#include "../Mob/Mine.h"
#include "../Input/InputDispatcher.h"
#include "../Scenes/GameScene.h"
#include "../GlobalScripts/ResourceManager.h"

ResourcePlace::ResourcePlace(int aLimit, Enums::ResourceTypes aResourceType)
    : limit(aLimit)
    , resourceType(aResourceType)
{
}

void ResourcePlace::setLimit(int amount)
{
    limit = amount;
}

Enums::ResourceTypes ResourcePlace::getResourceType() const
{
    return resourceType;
}

bool ResourcePlace::onClick(Position point)
{
    auto sprite = this->getSprite();
    if (!sprite)
    {
        return false;
    }

    if (parentScenePtr.expired())
    {
        return false;
    }

    auto gameScene = std::dynamic_pointer_cast<GameScene>(parentScenePtr.lock());

    if (gameScene != nullptr && gameScene->getGameSceneStatus() != Enums::GameSceneStatuses::Default)
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

    auto tempMineModel = GameModel::getInstance()->getMineModelByRes(resourceType);
    tempMineModel->setLimit(limit);

    Size resourcePlaceSize = sprite->getSize();
    auto tempMine = std::make_shared<Mine>(resourcePlaceSize);

    std::string mineName = tempMineModel->getName();

    tempMine->setMineModel(std::move(tempMineModel));

    auto sprt = std::make_shared<AnimationSceneSprite>(parentSceneShared->getRenderer());
    sprt->setTexture(ResourceManager::getInstance()->getTexture(mineName));

    auto anchorPair = sprite->getAnchorPoint();
    sprt->setAnchorPointPlace(anchorPair.first, anchorPair.second);
    tempMine->setName(mineName);
    tempMine->setTag("Mine");
    tempMine->setSprite(sprt);

    parentSceneShared->replaceObject(shared_from_this(), tempMine);

    return true;
}

bool ResourcePlace::update(double)
{
    return true;
}

void ResourcePlace::finalize()
{
}
