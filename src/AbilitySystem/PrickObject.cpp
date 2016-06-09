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
        list<SceneObject*> lst = parentScenePtr->findObjectsByTag("Monster");
        list<SceneObject*> lstResult;
        for(auto ptr = lst.begin(); ptr != lst.end(); ++ptr)
        {
            if (SDL_HasIntersection(&getSprite()->getRect(), &(*ptr)->getSprite()->getRect()))
                lstResult.insert(lstResult.end(), *ptr);
        }


        for(auto ptr2 = lstResult.begin(); ptr2 != lstResult.end(); ++ptr2)
        {
           DestructibleObject* temp = (*ptr2)->getDestructibleObject();
           if (temp != nullptr)
           {
               std::cout << "Damage to" << temp->getName() << std::endl;
               temp->receiveDamageOneType(Enums::DamageTypes::dtPHYSICAL, damage);
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
