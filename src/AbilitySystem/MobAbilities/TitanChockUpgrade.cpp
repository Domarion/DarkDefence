#include "TitanChockUpgrade.h"
#include "Scenes/GameScene.h"

TitanChockUpgrade::TitanChockUpgrade(std::shared_ptr<ManaGlobal> aManaModel)
    : MobAbility(aManaModel)
    , affectedMobs(std::make_unique<std::list<std::shared_ptr<SceneObject> > >())
    , stunEffect(std::make_shared<EffectModel>())
{
    pair<string, double> imbolizing = std::make_pair("Stun", 1);
//    pair<string, double> mv = std::make_pair("MoveSpeed", -2.0);
//    pair<string, double> rt = std::make_pair("ReloadTime", +5.0e+3);
    stunEffect->addMiniEffect(imbolizing);
    stunEffect->setCaption("Stun");
    stunEffect->setDuration(2000);
//    snowEffect->addMiniEffect(rt);
    srand(time(0));
}

void TitanChockUpgrade::releaseDamage(std::shared_ptr<SceneObject> aTarget)
{
    if (!aTarget->getEffectReceiver()->hasEffect(stunEffect) && (rand() % 2 == 1))
    {
        aTarget->getEffectReceiver()->applyEffect(stunEffect);
    }
    int dmgPhysical = static_cast<int>(Enums::DamageTypes::dtPHYSICAL);
    aTarget->getDestructibleObject()->receiveDamageOneType(dmgPhysical, 20);
    affectedMobs->push_back(aTarget);
}

void TitanChockUpgrade::init(std::shared_ptr<Scene> scenePtr)
{
    AbilityModel::init(scenePtr);

    auto gameScene = std::static_pointer_cast<GameScene>(scenePtr);

    if (gameScene != nullptr)
    {
       auto manaModel = gameScene->getManaModel();
       if (manaModel != nullptr)
       {
            auto regenValue = manaModel->getRegenValue() + 5;// учесть необходимость сброса в будущем
            manaModel->setRegenValue(regenValue);
       }
    }
}

bool TitanChockUpgrade::onReady(double /*timestep*/)
{
    if (target != nullptr)
    {
        affectedMobs->clear();

        auto monsters = parentScenePtr->findObjectsByTag("Monster");

        if (monsters == nullptr)
        {
            abilityState = Enums::AbilityStates::asNotAvaliable;
            return false;
        }

        int counter = 0;
        int counterMax = 14;

        for(auto& monster : *monsters)
        {
            if (monster != nullptr && monster != target)
            {
                releaseDamage(monster);

                ++counter;
                if (counter  == counterMax)
                    break;
            }
        }


        releaseDamage(target);
        abilityState = Enums::AbilityStates::asNotAvaliable;
    }
    return true;

}

bool TitanChockUpgrade::onWorking(double /*timestep*/)
{
    return true;

}

bool TitanChockUpgrade::onCooldown(double /*timestep*/)
{
    return true;
}

bool TitanChockUpgrade::canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate)
{
    MobAbility::setTarget(targ);
    return (targ != nullptr && targ->getTag() == "Monster" && aistate == Enums::AIMobStates::aiATTACK);
}

