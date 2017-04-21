#include "MobMageTowerAbility.h"
#include "Scenes/GameScene.h"

bool MobMageTowerAbility::onReady(double /*timestep*/)
{
    auto gameScene = std::static_pointer_cast<GameScene>(parentScenePtr);
    mManaModel = gameScene->getManaModel();
    if (mManaModel != nullptr)
    {
        int regenValue = mManaModel->getRegenValue() + 1;
        mManaModel->setRegenValue(regenValue);
    }
    abilityState = Enums::AbilityStates::asOnCooldown;
    return true;
}

bool MobMageTowerAbility::onWorking(double /*timestep*/)
{
    return true;
}

bool MobMageTowerAbility::onCooldown(double /*timestep*/)
{
    return true;
}

bool MobMageTowerAbility::canTrigger(std::shared_ptr<SceneObject>, Enums::AIMobStates)
{
    return abilityState == Enums::AbilityStates::asNotAvaliable;
}
