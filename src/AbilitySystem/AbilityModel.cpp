#include "AbilityModel.h"
#include "../GlobalScripts/GameModel.h"

#include <iostream>
AbilityModel::AbilityModel()
    :abilityState(Enums::AbilityStates::asNotAvaliable)
{

}

AbilityModel::~AbilityModel()
{

}

void AbilityModel::init(Scene * const scenePtr)
{
    parentScenePtr = scenePtr;
}



bool AbilityModel::onReady(double timestep)
{
  //  std::cout << "WHAT??????" << std::endl;

  return ( GameModel::getInstance()->getManaModel()->payMana(getManaCost()));

}

bool AbilityModel::onWorking(double timestep)
{
     return true;
}

bool AbilityModel::onCooldown(double timestep)
{
    return true;
}

bool AbilityModel::update(double timestep)
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
    }
     return true;
}

void AbilityModel::setAsReady()
{
    if (abilityState == Enums::AbilityStates::asNotAvaliable)
        abilityState = Enums::AbilityStates::asReady;
}

int AbilityModel::getManaCost() const
{
    return manaCost;
}

void AbilityModel::setManaCost(int value)
{
    manaCost = value;
}

double AbilityModel::getWorkTime() const
{
    return workTime;
}

void AbilityModel::setWorkTime(double value)
{
    workTime = value;
    currentWorkTime = workTime;
}

double AbilityModel::getCooldownTime() const
{
    return cooldownTime;
}

void AbilityModel::setCooldownTime(double value)
{
    cooldownTime = value;
    currentCooldownTime = cooldownTime;
}

string AbilityModel::getAbilityName() const
{
    return abilityName;
}

void AbilityModel::setAbilityName(const string &value)
{
    abilityName = value;
}
