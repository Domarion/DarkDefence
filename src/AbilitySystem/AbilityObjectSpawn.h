#pragma once

#include "AbilityModel.h"
#include "../AbilitySystem/AbilityAnims/AbilityAnimObject.hpp"
#include "../Input/InputHandler.h"
#include <cassert>

template<typename SpawnedObject>
class AbilityObjectSpawn: public AbilityModel, public InputHandler
{
public:
    AbilityObjectSpawn(std::shared_ptr<ManaGlobal> aManaModel);
    virtual ~AbilityObjectSpawn() = default;

    int getDamage() const;
    void setDamage(int value)
    {
        damage = value;
    }

    // AbilityModel interface
    bool onReady(double timestep) override;
    bool onWorking(double timestep) override;
    bool update(double timestep) override;
    bool canPlaceObject() const override;

    // InputHandler interface
    bool onClick(Position point) override;

private:
    int damage = 0;
    std::shared_ptr<SpawnedObject> someSpawnObject;
    int coordX = 0, coordY = 0;
};


template<typename SpawnedObject>
AbilityObjectSpawn<SpawnedObject>::AbilityObjectSpawn(std::shared_ptr<ManaGlobal> aManaModel)
    : AbilityModel(aManaModel)
    , damage(0)
{
}

template<typename SpawnedObject>
bool AbilityObjectSpawn<SpawnedObject>::onReady(double /*timestep*/)
{
    abilityState = Enums::AbilityStates::asWorking;
    return true;
}
template<typename SpawnedObject>
bool AbilityObjectSpawn<SpawnedObject>::onWorking(double /*timestep*/)
{
    if (parentScenePtr != nullptr && coordX > 0 && coordY > 0)
    {
        abilityState = Enums::AbilityStates::asOnCooldown;
        const int timeToLive = 200;
        someSpawnObject = std::make_shared<SpawnedObject>(timeToLive, damage);

        auto spriteBlink = std::make_shared<AnimationSceneSprite>(parentScenePtr->getRenderer());
        spriteBlink->setSize(Size(200, 200));
        spriteBlink->loadTexture("GameData/textures/EmptySlot.png");
        spriteBlink->setAnchorPointPlace(Enums::AnchorCoordTypes::Middle, Enums::AnchorCoordTypes::Middle);

        someSpawnObject->setSprite(spriteBlink);

        parentScenePtr->spawnObject(coordX, coordY, someSpawnObject);

        if (placingEndedCallBack)
        {
            placingEndedCallBack();
        }

        coordX = 0;
        coordY = 0;
    }
    return true;
}

template<typename SpawnedObject>
int AbilityObjectSpawn<SpawnedObject>::getDamage() const
{
    return damage;
}

template<typename SpawnedObject>
bool AbilityObjectSpawn<SpawnedObject>::update(double timestep)
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

template<typename SpawnedObject>
bool AbilityObjectSpawn<SpawnedObject>::canPlaceObject() const
{
    return true;
}

template<typename SpawnedObject>
bool AbilityObjectSpawn<SpawnedObject>::onClick(Position point)
{
    if (abilityState == Enums::AbilityStates::asWorking)
    {
        coordX = point.x;
        coordY = point.y;

        return true;
    }

    return false;
}
