#include "MobCloudTowerAbility.h"
#include "Scenes/GameScene.h"

MobCloudTowerAbility::MobCloudTowerAbility(std::shared_ptr<ManaGlobal> aManaModel)
    : MobAbility(aManaModel)
//    , affectedMobs(std::make_unique<std::list<std::shared_ptr<SceneObject> > >())
    , stunEffect(std::make_shared<EffectModel>())
{
    pair<string, double> imbolizing = std::make_pair("Stun", 1);
    stunEffect->addMiniEffect(imbolizing);
    stunEffect->setCaption("Stun");
    stunEffect->setDuration(2000);
    srand(time(0));
}

void MobCloudTowerAbility::releaseDamage(std::shared_ptr<SceneObject> aTarget)
{
    if (!aTarget->getEffectReceiver()->hasEffect(stunEffect) && (rand() % 10 == 1))
    {
        aTarget->getEffectReceiver()->applyEffect(stunEffect);
    }

    int dmgPhysical = static_cast<int>(Enums::DamageTypes::dtPHYSICAL);
    aTarget->getDestructibleObject()->receiveDamageOneType(dmgPhysical, 20);
//    affectedMobs->push_back(aTarget);
}

void MobCloudTowerAbility::init(std::shared_ptr<Scene> scenePtr)
{
    AbilityModel::init(scenePtr);

    auto gameScene = std::static_pointer_cast<GameScene>(scenePtr);

    if (gameScene != nullptr)
    {
        auto manaModel = gameScene->getManaModel();
        if (manaModel != nullptr)
        {
            // учесть необходимость сброса в будущем
            auto regenValue = manaModel->getRegenValue() + 5;
            manaModel->setRegenValue(regenValue);
        }
    }
}

bool MobCloudTowerAbility::onReady(double /*timestep*/)
{
    abilityState = Enums::AbilityStates::asNotAvaliable;

    if (target == nullptr)
    {
        return true;
    }

    auto monsters = parentScenePtr->findObjectsByTag("Monster");

    if (monsters == nullptr)
    {
        return false;
    }

    aBouncingArrowObject = Make_AbilityMultitargetObject("ArrowLighting", 5, parentScenePtr->getRenderer());

    if (aBouncingArrowObject)
    {
        aBouncingArrowObject->setParentScene(parentScenePtr);
        aBouncingArrowObject->SetCallBack(
            std::bind(&MobCloudTowerAbility::ChainLightingHandler, this, std::placeholders::_1));
        abilityState = Enums::AbilityStates::asWorking;
        auto fakePos = parentScenePtr->findObjectByTag("Tower")->getPosition();
        parentScenePtr->spawnObject(fakePos, aBouncingArrowObject);
    }

    return true;
}

bool MobCloudTowerAbility::onWorking(double /*timestep*/)
{
    return true;
}

bool MobCloudTowerAbility::onCooldown(double /*timestep*/)
{
    aBouncingArrowObject.reset();
    abilityState = Enums::AbilityStates::asNotAvaliable;
    return true;
}

bool MobCloudTowerAbility::canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate)
{
    MobAbility::setTarget(targ);
    return (targ != nullptr && targ->getTag() == "Monster"
        && aistate == Enums::AIMobStates::aiATTACK && abilityState == Enums::AbilityStates::asNotAvaliable);
}

void MobCloudTowerAbility::ChainLightingHandler(std::shared_ptr<SceneObject> aTarget)
{
    if (!aTarget)
    {
        abilityState = Enums::AbilityStates::asOnCooldown;
        return;
    }

    releaseDamage(aTarget);
}

