#include "AbilityMagicBlink.h"

AbilityMagicBlink::AbilityMagicBlink(std::shared_ptr<ManaGlobal> aManaModel)
    : AbilityModel(aManaModel)
    , damage(0)
    , someBlink(nullptr)
{
}

bool AbilityMagicBlink::onReady(double /*timestep*/)
{
    abilityState = Enums::AbilityStates::asWorking;
    return true;
}

bool AbilityMagicBlink::onWorking(double /*timestep*/)
{
    if (parentScenePtr != nullptr && coordX > 0 && coordY > 0)
    {
        abilityState = Enums::AbilityStates::asOnCooldown;
        const int timeToLive = 200;
        someBlink = std::make_shared<BlinkObject>(timeToLive, damage);

        auto spriteBlink = std::make_shared<AnimationSceneSprite>(parentScenePtr->getRenderer());
        spriteBlink->setSize(Size(200, 200));
        spriteBlink->loadTexture("GameData/textures/EmptySlot.png");
        spriteBlink->setAnchorPointPlace(Enums::AnchorCoordTypes::Middle, Enums::AnchorCoordTypes::Middle);

        someBlink->setSprite(spriteBlink);

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
