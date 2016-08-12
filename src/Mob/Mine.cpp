#include "Mine.h"
#include "ResourcePlace.h"

Mine::Mine()
    :model(nullptr)
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
                AnimatedSprite* resSprite = new AnimatedSprite();
                resSprite->setRect(0, 0, 200, 200);
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
}

DestructibleObject *Mine::getDestructibleObject()
{
    return model;
}

EffectReceiver *Mine::getEffectReceiver() const
{
    return nullptr;
}

MineModel *  Mine::getMineModel()
{
    return model;
}

void Mine::setMineModel(MineModel *  newModel)
{
   model = newModel;
}
