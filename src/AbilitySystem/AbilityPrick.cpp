#include "AbilityPrick.h"
//#include "Scenes/GameScene.h"

AbilityPrick::AbilityPrick(std::shared_ptr<ManaGlobal> aManaModel)
    : AbilityModel(aManaModel)
    , damage(0)
    , somePrick(nullptr)
    , coordX(0)
    , coordY(0)
{

}

bool AbilityPrick::onReady(double /*timestep*/)
{
    abilityState = Enums::AbilityStates::asWorking;

    return true;
}

bool AbilityPrick::onWorking(double /*timestep*/)
{
    if (parentScenePtr != nullptr && coordX > 0 && coordY > 0)
    {
        abilityState = Enums::AbilityStates::asOnCooldown;
        const int timeToLive = 200;
        somePrick = std::make_shared<PrickObject>(timeToLive, damage);

        auto spritePrick = std::make_shared<AnimationSceneSprite>(parentScenePtr->getRenderer());
        spritePrick->setSize(Size(200, 200));
        spritePrick->loadTexture("GameData/textures/EmptySlot.png");
        somePrick->setSprite(spritePrick);

        parentScenePtr->spawnObject(coordX, coordY, somePrick);

        if (placingEndedCallBack)
        {
            placingEndedCallBack();
        }

        coordX = 0;
        coordY = 0;


    }
    return true;
}

bool AbilityPrick::onCooldown(double timestep)
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

int AbilityPrick::getDamage() const
{
    return damage;
}

void AbilityPrick::setDamage(int value)
{
    damage = value;
}

bool AbilityPrick::update(double timestep)
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

bool AbilityPrick::canPlaceObject() const
{
    return true;
}


bool AbilityPrick::onClick(Position point)
{
    if (abilityState == Enums::AbilityStates::asWorking)
    {
//        auto gameScene = std::dynamic_pointer_cast<GameScene>(parentScenePtr);
//        if (gameScene != nullptr && gameScene->getGameSceneStatus() != Enums::GameSceneStatuses::SpellCasting)
//        {
//            return false;
//        }
//        else
//        {
//            gameScene->setGameSceneStatus(Enums::GameSceneStatuses::Default);

//        }
        coordX = point.x;
        coordY = point.y;

        return true;
    }

    return false;
}
