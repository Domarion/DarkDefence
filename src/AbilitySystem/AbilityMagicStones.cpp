#include "AbilityMagicStones.h"

AbilityMagicStones::AbilityMagicStones(std::shared_ptr<ManaGlobal> aManaModel)
    : AbilityModel(aManaModel)
    , gatesSceneObject(nullptr)
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
    StoneEffect = std::make_shared<EffectModel>();
    StoneEffect->addMiniEffect(miniProtection);
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
        gatesSceneObject->getEffectReceiver()->applyEffect(StoneEffect);
        abilityState = Enums::AbilityStates::asWorking;
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
            gatesSceneObject->getEffectReceiver()->cancelEffect(StoneEffect);

        currentWorkTime = workTime;
        abilityState = Enums::AbilityStates::asOnCooldown;
    }
    else
        currentWorkTime -= timestep;

    return true;
}

bool AbilityMagicStones::onCooldown(double timestep)
{
    static double currentDelta = 0; //чтобы не спамить
    const double spamDelta = 250; // интервал передачи значений

    if (currentCooldownTime <= 0)
    {
        currentCooldownTime = cooldownTime;
        abilityState = Enums::AbilityStates::asNotAvaliable;
    }
    else
    {
        currentCooldownTime -= timestep;

        currentDelta += timestep;

        if (currentDelta > spamDelta && cooldownListener != nullptr)
        {

            currentDelta = 0;
            int current = static_cast<int>(cooldownTime - currentCooldownTime);
            int max = static_cast<int>(cooldownTime);

            cooldownListener(current, max);
        }
    }

    return true;
}
