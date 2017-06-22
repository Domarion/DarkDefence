#include "ResourcePlace.h"
#include "../GlobalScripts/GameModel.h"
#include "../Mob/Mine.h"
#include <iostream>
#include "../Input/InputDispatcher.h"
#include "../Scenes/GameScene.h"
#include "../GlobalScripts/ResourceManager.h"

ResourcePlace::ResourcePlace()
    : ResourcePlace(1000, Enums::ResourceTypes::WHEAT)
{
}

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
    if (getSprite() == nullptr)
        return false;

    auto gameScene = std::dynamic_pointer_cast<GameScene>(parentScenePtr.lock());

    if (gameScene != nullptr && gameScene->getGameSceneStatus() != Enums::GameSceneStatuses::Default)
    {
        return false;
    }

    SDL_Point sPoint{point.x, point.y};

    SDL_Rect rect = {this->getSprite()->getRealPosition().x
                     , this->getSprite()->getRealPosition().y
                     , this->getSprite()->getSize().width
                     , this->getSprite()->getSize().height
                    };
    if (SDL_PointInRect(&sPoint, &rect))
    {
        auto tempMineModel = GameModel::getInstance()->getMineModelByRes(resourceType);
        tempMineModel->setLimit(limit);

        Size resourcePlaceSize = getSprite()->getSize();
        auto tempMine = std::make_shared<Mine>(resourcePlaceSize);

        std::string mineName = tempMineModel->getName();

        tempMine->setMineModel(std::move(tempMineModel));

        auto sprt = std::make_shared<AnimationSceneSprite>(parentScenePtr.lock()->getRenderer());
        sprt->setTexture(ResourceManager::getInstance()->getTexture(mineName));

        auto anchorPair = getSprite()->getAnchorPoint();
        sprt->setAnchorPointPlace(anchorPair.first, anchorPair.second);
        tempMine->setName(mineName);
        tempMine->setTag("Mine");
        tempMine->setSprite(sprt);

        parentScenePtr.lock()->replaceObject(shared_from_this(), tempMine);

        return true;
    }

    return false;
}

bool ResourcePlace::update(double)
{
    return true;
}

void ResourcePlace::finalize()
{
}
