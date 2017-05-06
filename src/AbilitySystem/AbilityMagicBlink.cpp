#include "AbilityMagicBlink.h"
#include "../GlobalScripts/GameModel.h"

AbilityMagicBlink::AbilityMagicBlink(std::shared_ptr<ManaGlobal> aManaModel)
    : AbilityModel(aManaModel)
    , damage(0)
    , someBlink(nullptr)
{
}


bool AbilityMagicBlink::onReady(double /*timestep*/)
{
    abilityState = Enums::AbilityStates::asWorking;

//    if (affectedMobs == nullptr && parentScenePtr != nullptr && GameModel::getInstance()->getMonsterCount() > 0)
//        affectedMobs = parentScenePtr->findObjectsByTag("Monster");

//    if (affectedMobs != nullptr)
//    {
//        if (affectedMobs != nullptr && affectedMobs->size() > 0)
//            for(auto affectedMob = affectedMobs->begin(); affectedMob != affectedMobs->end(); ++affectedMob)
//            {
//                if (*affectedMob != nullptr && (*affectedMob)->getDestructibleObject() != nullptr)
//                {
//                    (*affectedMob)->setVisible(true);
//                    (*affectedMob)->getDestructibleObject()->receiveDamageOneType(3, damage);
//                }
//            }
//        abilityState = Enums::AbilityStates::asOnCooldown;
//    }
//    else
//        abilityState = Enums::AbilityStates::asNotAvaliable;

    return true;
}

bool AbilityMagicBlink::onWorking(double /*timestep*/)
{
    if (parentScenePtr != nullptr && coordX > 0 && coordY > 0)
    {
        abilityState = Enums::AbilityStates::asOnCooldown;
        const int timeToLive = 200;
        someBlink = std::make_shared<BlinkObject>(timeToLive, damage);

        auto spritePrick = std::make_shared<AnimationSceneSprite>(parentScenePtr->getRenderer());
        spritePrick->setSize(Size(200, 200));
        spritePrick->loadTexture("GameData/textures/EmptySlot.png");
        someBlink->setSprite(spritePrick);

        parentScenePtr->spawnObject(coordX, coordY, someBlink);

        if (placingEndedCallBack)
        {
            placingEndedCallBack();
        }

        coordX = 0;
        coordY = 0;


    }
    return true;
}

bool AbilityMagicBlink::onCooldown(double timestep)
{
    if (currentCooldownTime <= 0)
    {
        currentCooldownTime = cooldownTime;
        abilityState = Enums::AbilityStates::asNotAvaliable;
    }
    else
        currentCooldownTime -= timestep;

    return true;
}

int AbilityMagicBlink::getDamage() const
{
    return damage;
}

void AbilityMagicBlink::setDamage(int value)
{
    damage = value;
}

bool AbilityMagicBlink::update(double timestep)
{
    switch(abilityState)
    {
        case Enums::AbilityStates::asReady:
        {
            onReady(timestep);
            break;
        }

        case Enums::AbilityStates::asWorking:
        {
            onWorking(timestep);
            break;
        }
        case Enums::AbilityStates::asOnCooldown:
        {
            onCooldown(timestep);
            break;
        }
        case Enums::AbilityStates::asNotAvaliable:
        {
            break;
        }
    }

    return true;
}

bool AbilityMagicBlink::canPlaceObject() const
{
    return true;
}

bool AbilityMagicBlink::onClick(Position point)
{
    if (abilityState == Enums::AbilityStates::asWorking)
    {
        coordX = point.x;
        coordY = point.y;

        return true;
    }

    return false;
}
