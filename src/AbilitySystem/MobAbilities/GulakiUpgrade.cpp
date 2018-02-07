#include "GulakiUpgrade.h"

GulakiUpgrade::GulakiUpgrade(std::shared_ptr<ManaGlobal> aManaModel)
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

void GulakiUpgrade::releaseDamage(std::shared_ptr<SceneObject> aTarget)
{
    if (!aTarget->getEffectReceiver()->hasEffect(stunEffect) && (rand() % 3 == 1))
    {
        aTarget->getEffectReceiver()->applyEffect(stunEffect);
    }

    int dmgPhysical = static_cast<int>(Enums::DamageTypes::dtPHYSICAL);
    aTarget->getDestructibleObject()->receiveDamageOneType(dmgPhysical, 20);
//    affectedMobs->push_back(aTarget);
}

bool GulakiUpgrade::onReady(double /*timestep*/)
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

    aBouncingArrowObject = Make_AbilityMultitargetObject("ArrowLighting", 2, parentScenePtr->getRenderer());

    if (aBouncingArrowObject)
    {
        aBouncingArrowObject->setParentScene(parentScenePtr);
        aBouncingArrowObject->SetCallBack(
            std::bind(&GulakiUpgrade::ChainLightingHandler, this, std::placeholders::_1));
        abilityState = Enums::AbilityStates::asWorking;
        auto fakePos = parentScenePtr->findObjectByTag("Tower")->getPosition();
        parentScenePtr->spawnObject(fakePos, aBouncingArrowObject);
    }

    return true;
}

bool GulakiUpgrade::onWorking(double /*timestep*/)
{
    return true;
}

bool GulakiUpgrade::onCooldown(double /*timestep*/)
{
    aBouncingArrowObject.reset();
    abilityState = Enums::AbilityStates::asNotAvaliable;

    return true;
}

bool GulakiUpgrade::canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate)
{
    MobAbility::setTarget(targ);
    return (targ != nullptr && targ->getTag() == "Monster"
        && aistate == Enums::AIMobStates::aiATTACK && abilityState == Enums::AbilityStates::asNotAvaliable);
}

void GulakiUpgrade::ChainLightingHandler(std::shared_ptr<SceneObject> aTarget)
{
    if (!aTarget)
    {
        abilityState = Enums::AbilityStates::asOnCooldown;
        return;
    }

    releaseDamage(aTarget);
}
