#include "Mine.h"
#include "ResourcePlace.h"
#include "../GlobalScripts/GameModel.h"

Mine::Mine(Size aResourcePlaceSize)
    : model(nullptr)
    , mineEffectReceiver(std::make_shared<DestructibleObjectEffectReceiver>())
    , mResourcePlaceSize(aResourcePlaceSize)
{
}

bool Mine::update(double timestep)
{
    if (model != nullptr)
    {
        model->produce(timestep, GameModel::getInstance()->getResourcesModel());

        if (model->getLimit() <= 0)
            return false;

        if (model->getCurrentHealth() <= 0)
        {
            int resPlaceLimit = model->calculateLimitAfterDestruction();
            if (resPlaceLimit <= 0)
                return false;

            auto resPlace = std::make_shared<ResourcePlace>(resPlaceLimit, model->getProductionType());
            auto resSprite = std::make_shared<AnimationSceneSprite>(parentScenePtr.lock()->getRenderer());
            resSprite->setSize(mResourcePlaceSize);

            auto resourceName =
                GameModel::getInstance()->getResourcesModel()->getResourceNameFromType(model->getProductionType());

            resSprite->loadTexture("GameData/textures/Resources/" + resourceName + "Resource.png");

            auto anchorPair = getSprite()->getAnchorPoint();
            resSprite->setAnchorPointPlace(anchorPair.first, anchorPair.second);

            resPlace->setSprite(resSprite);
            resPlace->setName("ResourcePlace");
            resPlace->setTag("ResourcePlace");

            parentScenePtr.lock()->spawnObject(WorldPosition, resPlace);

            return false;
        }
    }

    return true;
}

void Mine::finalize()
{
    model.reset();
    mineEffectReceiver.reset();
}

std::shared_ptr<DestructibleObject> Mine::getDestructibleObject() const
{
    return model;
}

std::shared_ptr<EffectReceiver> Mine::getEffectReceiver() const
{
    return mineEffectReceiver;
}

std::shared_ptr<MineModel> Mine::getMineModel()
{
    return model;
}

void Mine::setMineModel(std::shared_ptr<MineModel>  newModel)
{
    model = newModel;
}
