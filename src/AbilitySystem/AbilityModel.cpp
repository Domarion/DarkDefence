#include "AbilityModel.h"
#include "../Grouping/Scene.h"

AbilityModel::AbilityModel(std::shared_ptr<ManaGlobal> aManaModel)
    : abilityState(Enums::AbilityStates::asNotAvaliable)
    , abilityName("none")
    , manaCost(0)
    , workTime(0.0)
    , currentWorkTime(0.0)
    , cooldownTime(0.0)
    , currentCooldownTime(0.0)
    , mManaModel(aManaModel)
{
}

void AbilityModel::init(std::shared_ptr<Scene> scenePtr)
{
    parentScenePtr = scenePtr;
}

bool AbilityModel::onCooldown(double timestep)
{
    if (currentCooldownTime <= 0)
    {
        currentCooldownTime = cooldownTime;
        abilityState = Enums::AbilityStates::asNotAvaliable;
        currentDelta = 0;
        return true;
    }

    currentCooldownTime -= timestep;

    currentDelta += timestep;

    if (cooldownListener != nullptr && currentDelta > spamDelta)
    {
        currentDelta = 0;
        int current = static_cast<int>(cooldownTime - currentCooldownTime);
        int max = static_cast<int>(cooldownTime);

        cooldownListener(current, max);
    }

    return false;
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
        case Enums::AbilityStates::asNotAvaliable:
        {
            break;
        }
    }
     return true;
}

bool AbilityModel::trySetAsReady()
{
    if (abilityState == Enums::AbilityStates::asNotAvaliable && mManaModel->payMana(getManaCost()))
    {
        abilityState = Enums::AbilityStates::asReady;
        return true;
    }

    return false;
}

bool AbilityModel::setAsReady()
{
    if (abilityState == Enums::AbilityStates::asNotAvaliable)
    {
        abilityState = Enums::AbilityStates::asReady;
        return true;
    }

    return false;
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

double AbilityModel::getCurrentCooldownTime() const
{
    return currentCooldownTime;
}

void AbilityModel::setCooldownTime(double value)
{
    cooldownTime = value;
    currentCooldownTime = cooldownTime;
}

const std::string& AbilityModel::getAbilityName() const
{
    return abilityName;
}

void AbilityModel::setAbilityName(const std::string& aName)
{
    abilityName = aName;
}

bool AbilityModel::canPlaceObject() const
{
    return false;
}

void AbilityModel::setPlacingCallback(std::function<void ()> aPlacingEndedCallBack)
{
    placingEndedCallBack = aPlacingEndedCallBack;
}

void AbilityModel::connectCooldownListener(std::function<void (int, int)> aMethod)
{
    cooldownListener = aMethod;
}
