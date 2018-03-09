#include "MobAbilityWheat.h"
#include "../../GlobalScripts/GameModel.h"

bool MobAbilityWheat::onReady(double)
{
    abilityState = Enums::AbilityStates::asWorking;
    return true;
}

bool MobAbilityWheat::onWorking(double timestep)
{
    if (currentWorkTime <= 0)
    {
        currentWorkTime = workTime;
        int resType = static_cast<int>(Enums::ResourceTypes::WHEAT);
        GameModel::getInstance()->getResourcesModel()->addResource(resType,10);
    }
    else
    {
        currentWorkTime -= timestep;
    }

    return true;
}

bool MobAbilityWheat::canTrigger(std::shared_ptr<SceneObject>, Enums::AIMobStates /*aistate*/)
{
    return abilityState == Enums::AbilityStates::asNotAvaliable;
}

bool MobAbilityWheat::onCooldown(double)
{
    return true;
}
