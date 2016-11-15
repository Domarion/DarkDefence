#include "Mine.h"
#include "ResourcePlace.h"
#include "../GlobalScripts/GameModel.h"

Mine::Mine()
    : model(nullptr)
    , mineEffectReceiver(std::make_shared<DestructibleObjectEffectReceiver>())
{

}


bool Mine::update(double timestep)
{

    if (model != nullptr)
    {
        model->produce(timestep);

        if (model->getLimit() <= 0)
            return false;

        std::cout << "current mine health = " << (model->getCurrentHealth()) << std::endl;
        if (model->getCurrentHealth() <= 0)
        {
            auto resPlace = std::make_shared<ResourcePlace>(model->getLimit(), model->getProductionType());
            auto resSprite = std::make_shared<AnimationSceneSprite>(parentScenePtr.lock()->getRenderer());
            resSprite->setSize(Size(200, 200));

            std::string resourceName = GameModel::getInstance()->getResourcesModel()->getResourceNameFromIndex(static_cast<size_t>(model->getProductionType()));
            resSprite->loadTexture("GameData/textures/Resources/" + resourceName + "Resource.png");
            resPlace->setSprite(resSprite);
            resPlace->setName("ResourcePlace");
            resPlace->setTag("ResourcePlace");

            parentScenePtr.lock()->spawnObject(x, y, resPlace);

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

std::shared_ptr<MineModel>  Mine::getMineModel()
{
    return model;
}

void Mine::setMineModel(std::shared_ptr<MineModel>  newModel)
{
   model = newModel;
}
