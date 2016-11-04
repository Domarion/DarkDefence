#include "Mine.h"
#include "ResourcePlace.h"

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
           // model->setLimit(0);

            if (model->getLimit() > 0)
            {
                auto resPlace = std::make_shared<ResourcePlace>();
                auto resSprite = std::make_shared<AnimationSceneSprite>(parentScenePtr.lock()->getRenderer());
                resSprite->setSize(Size(200, 200));
                resSprite->loadTexture("GameData/textures/Resources/WheatResource.png");
                resPlace->setSprite(resSprite);
                resPlace->setName("ResourcePlace");
                resPlace->setTag("ResourcePlace");

                parentScenePtr.lock()->spawnObject(x, y, resPlace);
                resPlace->setLimit(model->getLimit());
            }
            return false;
        }
    }

    return true;
}

void Mine::finalize()
{
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
