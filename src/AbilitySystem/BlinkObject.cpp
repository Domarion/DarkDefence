#include "BlinkObject.h"

BlinkObject::BlinkObject(int aTimeToLive, int aDamage)
    : AbilityAnimObject(aTimeToLive)
    , damage(aDamage)
{

}

void BlinkObject::init(int x, int y)
{
    SceneObject::init(x, y);

    if (!parentScenePtr.expired())
    {
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
               (*affectedMob)->setVisible(true);
               temp->receiveDamageOneType(static_cast<int>(Enums::DamageTypes::dtFIRE), damage);
           }
        }
    }
}
