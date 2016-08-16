#include "AbilityPrick.h"
#include <iostream>
AbilityPrick::AbilityPrick()
    :damage(0), somePrick(nullptr), coordX(0), coordY(0)
{

}

AbilityPrick::~AbilityPrick()
{

}

void AbilityPrick::init(Scene * const scenePtr)
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



   // else
     //   abilityState = Enums::AbilityStates::asNotAvaliable;

    return true;
}

bool AbilityPrick::onWorking(double timestep)
{
    if (parentScenePtr != nullptr && coordX > 0 && coordY > 0)
    {
        abilityState = Enums::AbilityStates::asOnCooldown;
        std::cout << "prickEnter" << std::endl;
        somePrick = new PrickObject(damage);
       AnimatedSprite* sptr = new AnimatedSprite();
        sptr->setRect(0,0, 200, 200);
        sptr->loadTexture("GameData/textures/EmptySlot.png");
        somePrick->setSprite(sptr);

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
        std::cout << "WTF CLICKED" << std::endl;

        return true;
    }
    return false;
}
