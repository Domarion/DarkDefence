#include "AbilityPrick.h"
AbilityPrick::AbilityPrick(std::shared_ptr<ManaGlobal> aManaModel)
    : AbilityModel(aManaModel)
    , damage(0)
    , somePrick(nullptr)
    , coordX(0)
    , coordY(0)
{

}

AbilityPrick::~AbilityPrick()
{

}

void AbilityPrick::init(std::shared_ptr<Scene> scenePtr)
{
    AbilityModel::init(scenePtr);
}

bool AbilityPrick::onReady(double timestep)
{
    if (AbilityModel::onReady(timestep) == false)
    {

        abilityState = Enums::AbilityStates::asNotAvaliable;

        return false;
    }
    else
    {
        abilityState =Enums::AbilityStates::asWorking;
    }

    return true;
}

bool AbilityPrick::onWorking(double timestep)
{
    if (parentScenePtr != nullptr && coordX > 0 && coordY > 0)
    {
        abilityState = Enums::AbilityStates::asOnCooldown;
        somePrick = std::make_shared<PrickObject>(damage);

        auto spritePrick = std::make_shared<AnimationSceneSprite>(parentScenePtr->getRenderer());
        spritePrick->setSize(Size(200, 200));
        spritePrick->loadTexture("GameData/textures/EmptySlot.png");
        somePrick->setSprite(spritePrick);

        parentScenePtr->spawnObject(coordX,coordY, somePrick);
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

    if (cooldownTime - currentCooldownTime < 100 && cooldownTime - currentCooldownTime > 80)
    {
        parentScenePtr->destroyObject(somePrick);
    }
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


bool AbilityPrick::onClick(SDL_Point *point)
{
    if (abilityState == Enums::AbilityStates::asWorking)
    {
        coordX = point->x;
        coordY = point->y;

        return true;
    }
    return false;
}
