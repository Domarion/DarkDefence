#include "AbilityMagicStones.h"
#include <iostream>
AbilityMagicStones::AbilityMagicStones()
    :gatesSceneObject(nullptr)
{

}

AbilityMagicStones::~AbilityMagicStones()
{
    gatesSceneObject = nullptr;
}

void AbilityMagicStones::init(std::shared_ptr<Scene> scenePtr)
{
    AbilityModel::init(scenePtr);
    pair<string, double> miniProtection = std::make_pair("Protection", +500);
    StoneEffect.addMiniEffect(miniProtection);
}

bool AbilityMagicStones::onReady(double timestep)
{
    if (AbilityModel::onReady(timestep) == false)
    {
        abilityState = Enums::AbilityStates::asNotAvaliable;

        return false;
    }

    if (gatesSceneObject == nullptr && parentScenePtr != nullptr)
        gatesSceneObject = parentScenePtr->findObjectByTag("Gates");

    if (gatesSceneObject != nullptr)
    {
        gatesSceneObject->getEffectReceiver()->applyEffect(&StoneEffect);
        abilityState = Enums::AbilityStates::asWorking;
         std::cout << "worked" << std::endl;
    }
    else
        abilityState = Enums::AbilityStates::asNotAvaliable;

    return true;
}

bool AbilityMagicStones::onWorking(double timestep)
{
    if (currentWorkTime <= 0)
    {
        if (gatesSceneObject != nullptr)
            gatesSceneObject->getEffectReceiver()->cancelEffect(&StoneEffect);

        currentWorkTime = workTime;
        abilityState = Enums::AbilityStates::asOnCooldown;
    }
    else
        currentWorkTime -= timestep;

    //std::cout << "worked" << std::endl;
    return true;
}

bool AbilityMagicStones::onCooldown(double timestep)
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
