#include "MobEarthTowerAbility.h"
#include "Mob/Gates.h"
#include "GlobalScripts/GameModel.h"

MobEarthTowerAbility::MobEarthTowerAbility()
    : MobAbility()
    , gates(nullptr)
    , effect(std::make_shared<EffectModel>())
{
    pair<string, double> miniProtection = std::make_pair("ProtectionPercent", 0.25);
    pair<string, double> miniHealth = std::make_pair("HealthPercent", 0.25);

    effect->addMiniEffect(miniProtection);
    effect->addMiniEffect(miniHealth);
}

bool MobEarthTowerAbility::onReady(double /*timestep*/)
{
    gates = parentScenePtr->findObjectByTag("Gates");
    if (gates == nullptr)
    {
        abilityState = Enums::AbilityStates::asNotAvaliable;
    }
    else
    {
        currentWorkTime = workTime;

        auto effectReceiver = gates->getEffectReceiver();
        effectReceiver->applyEffect(effect);
        abilityState = Enums::AbilityStates::asWorking;
    }
    return true;
}

bool MobEarthTowerAbility::onCooldown(double /*timestep*/)
{
    return false;
}

bool MobEarthTowerAbility::onWorking(double timestep)
{
    if (currentWorkTime == 0)
    {
        currentWorkTime = workTime;

        if (gates != nullptr)
        {
            int resType = static_cast<int>(Enums::ResourceTypes::WHEAT);
            GameModel::getInstance()->getResourcesModel()->addResource(resType,10);

            resType = static_cast<int>(Enums::ResourceTypes::STONE);
            GameModel::getInstance()->getResourcesModel()->addResource(resType,10);
        }
        else
            abilityState = Enums::AbilityStates::asOnCooldown;
    }
    else
        currentWorkTime -= timestep;

    return true;
}

bool MobEarthTowerAbility::canTrigger(std::shared_ptr<SceneObject>, Enums::AIMobStates)
{
    return abilityState == Enums::AbilityStates::asNotAvaliable;
}
