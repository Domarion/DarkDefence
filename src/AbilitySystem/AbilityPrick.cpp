#include "AbilityPrick.h"

AbilityPrick::AbilityPrick()
    :somePrick(nullptr), coordX(0), coordY(0)
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

    if (parentScenePtr != nullptr && coordX > 0 && coordY > 0)
    {
        somePrick = new PrickObject(damage);
       Sprite* sptr = new Sprite();
        sptr->setRect(0,0, 200, 200);
        sptr->setTexture(Renderer::getInstance()->loadTextureFromFile("/home/kostya_hm/Projects/DarkDefence/GameData/textures/EmptySlot.png"));
        somePrick->setSprite(sptr);

        parentScenePtr->spawnObject(coordX,coordY, somePrick);
        coordX = 0;
        coordY = 0;

        abilityState = Enums::AbilityStates::asOnCooldown;
    }
    else
        abilityState = Enums::AbilityStates::asNotAvaliable;

    return true;
}

bool AbilityPrick::onWorking(double timestep)
{
    return false;
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

bool AbilityPrick::onClick(SDL_Point *point)
{

    if (abilityState == Enums::AbilityStates::asReady)
    {
        coordX = point->x;
        coordY = point->y;
        return true;
    }
    return false;
}
