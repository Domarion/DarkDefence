#include "Mine.h"
#include "ResourcePlace.h"

Mine::Mine()
    :model(nullptr),mineEffectReceiver(new DestructibleObjectEffectReceiver())
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
                ResourcePlace* resPlace = new ResourcePlace();
                auto resSprite = std::make_shared<AnimationSceneSprite>(parentScenePtr->getRenderer());
                resSprite->setSize(Size(200, 200));
                resSprite->loadTexture("GameData/textures/Resources/WheatResource.png");
                resPlace->setSprite(resSprite);
                resPlace->setName("ResourcePlace");
                resPlace->setTag("ResourcePlace");

                parentScenePtr->spawnObject(x, y, resPlace);
                resPlace->setLimit(model->getLimit());
            }
            return false;
        }
    }

    return true;
}

void Mine::finalize()
{
    delete model;
    delete mineEffectReceiver;
}

DestructibleObject *Mine::getDestructibleObject()
{
    return model;
}

EffectReceiver *Mine::getEffectReceiver() const
{
    return mineEffectReceiver;
}

MineModel *  Mine::getMineModel()
{
    return model;
}

void Mine::setMineModel(MineModel *  newModel)
{
   model = newModel;
}
