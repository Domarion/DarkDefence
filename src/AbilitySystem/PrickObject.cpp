#include "PrickObject.h"
#include "../Enums.h"
#include <iostream>

PrickObject::PrickObject(int aDamage)
    :notDid(true), damage(aDamage)
{

}

PrickObject::~PrickObject()
{

}

void PrickObject::init(int x, int y)
{
    SceneObject::init(x, y);

    if (!parentScenePtr.expired())
    {
        std::cout << "prickObject init" << std::endl;
        auto mobListWithTag = parentScenePtr.lock()->findObjectsByTag("Monster");

        if (mobListWithTag == nullptr)
            return;

        list<std::shared_ptr<SceneObject>> affectedMobs;
        for(auto mobWithTag =mobListWithTag->begin(); mobWithTag != mobListWithTag->end(); ++mobWithTag)
        {
            SDL_Rect prickRect = {this->getSprite()->getPosition().x
                                  , this->getSprite()->getPosition().y
                                  , this->getSprite()->getSize().width
                                  , this->getSprite()->getSize().height
                                  };

            SDL_Rect mobRect = {(*mobWithTag)->getSprite()->getPosition().x
                                  , (*mobWithTag)->getSprite()->getPosition().y
                                  , (*mobWithTag)->getSprite()->getSize().width
                                  , (*mobWithTag)->getSprite()->getSize().height
                                  };

            if (SDL_HasIntersection(&prickRect,&mobRect))
                affectedMobs.insert(affectedMobs.end(), (*mobWithTag));
        }

        mobListWithTag->clear();

        for(auto affectedMob = affectedMobs.begin(); affectedMob != affectedMobs.end(); ++affectedMob)
        {
           auto temp = (*affectedMob)->getDestructibleObject();
           if (temp != nullptr)
           {
               std::cout << "Damage to" << temp->getName() << std::endl;
               temp->receiveDamageOneType(static_cast<int>(Enums::DamageTypes::dtPHYSICAL), damage);
           }
        }
        notDid = false;
    }
}

bool PrickObject::update(double /*timestep*/)
{
    return notDid;
}

void PrickObject::finalize()
{

}
