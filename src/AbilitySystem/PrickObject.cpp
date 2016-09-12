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

    if (parentScenePtr != nullptr)
    {
        std::cout << "prickObject init" << std::endl;
        list<SceneObject*>* mobListWithTag = parentScenePtr->findObjectsByTag("Monster");

        if (mobListWithTag == nullptr)
            return;

        list<SceneObject*> affectedMobs;
        for(auto mobWithTag = mobListWithTag->begin(); mobWithTag != mobListWithTag->end(); ++mobWithTag)
        {
            if (SDL_HasIntersection(&getSprite()->getRect(), &(*mobWithTag)->getSprite()->getRect()))
                affectedMobs.insert(affectedMobs.end(), *mobWithTag);
        }

        mobListWithTag->clear();
        delete mobListWithTag;
        mobListWithTag = nullptr;

        for(auto affectedMob = affectedMobs.begin(); affectedMob != affectedMobs.end(); ++affectedMob)
        {
           DestructibleObject* temp = (*affectedMob)->getDestructibleObject();
           if (temp != nullptr)
           {
               std::cout << "Damage to" << temp->getName() << std::endl;
               temp->receiveDamageOneType(static_cast<int>(Enums::DamageTypes::dtPHYSICAL), damage);
           }
        }
        notDid = false;
    }
}

bool PrickObject::update(double timestep)
{
    return notDid;
}

void PrickObject::finalize()
{

}
