#include "BlinkObject.h"
#include "Logging/Logger.h"

BlinkObject::BlinkObject(int aTimeToLive, int aDamage)
    : AbilityAnimObject(aTimeToLive)
    , damage(aDamage)
{
}

void BlinkObject::init(int x, int y)
{
    SceneObject::init(x, y);

    if (parentScenePtr.expired())
    {
        return;
    }

    auto mobListWithTag = parentScenePtr.lock()->findObjectsByTag("Monster");

    if (mobListWithTag == nullptr)
        return;

    for(const auto& mobWithTag : *mobListWithTag)
    {
        if (!mobListWithTag)
        {
            continue;
        }

        SDL_Rect prickRect = {this->getSprite()->getPosition().x
                              , this->getSprite()->getPosition().y
                              , this->getSprite()->getSize().width
                              , this->getSprite()->getSize().height
                              };

        SDL_Rect mobRect = {mobWithTag->getSprite()->getPosition().x
                              , mobWithTag->getSprite()->getPosition().y
                              , mobWithTag->getSprite()->getSize().width
                              , mobWithTag->getSprite()->getSize().height
                              };

        if (SDL_HasIntersection(&prickRect,&mobRect))
            mAffectedMobs.insert(mAffectedMobs.end(), mobWithTag);
    }

    mobListWithTag->clear();
}

bool BlinkObject::update(double aTimeStep)
{
    if (isFinished())
    {
        LOG_INFO("isFinished");
        for (auto& affectedMob : mAffectedMobs)
        {
           if (!affectedMob)
           {
               continue;
           }

           auto temp = affectedMob->getDestructibleObject();
           if (temp != nullptr)
           {
               affectedMob->setVisible(true);
               temp->receiveDamageOneType(static_cast<int>(Enums::DamageTypes::dtFIRE), damage);
           }
        }
        mAffectedMobs.clear();
    }

    return AbilityAnimObject::update(aTimeStep);
}
