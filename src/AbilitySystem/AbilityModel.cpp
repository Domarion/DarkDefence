#include "AbilityModel.h"

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

}

bool AbilityModel::onWorking(double timestep)
{

}

bool AbilityModel::onCooldown(double timestep)
{

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
}

void AbilityModel::setAsReady()
{
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
