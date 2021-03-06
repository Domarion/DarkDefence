#include "AbilityMagicStones.h"
#include "../Grouping/Scene.h"

AbilityMagicStones::AbilityMagicStones(std::shared_ptr<ManaGlobal> aManaModel)
    : AbilityModel(aManaModel)
{
}

void AbilityMagicStones::init(std::shared_ptr<Scene> scenePtr)
{
    AbilityModel::init(scenePtr);
    pair<string, double> miniProtection = std::make_pair("Protection", +500);
    StoneEffect = std::make_shared<EffectModel>();
    StoneEffect->addMiniEffect(miniProtection);
}

bool AbilityMagicStones::onReady(double /*timestep*/)
{
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
