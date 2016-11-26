#include "GulakiUpgrade.h"

GulakiUpgrade::GulakiUpgrade(std::shared_ptr<ManaGlobal> aManaModel)
    : MobAbility(aManaModel)
    , affectedMobs(std::make_unique<std::list<std::shared_ptr<SceneObject> > >())
    , snowEffect(std::make_shared<EffectModel>())
{
    pair<string, double> mv = std::make_pair("MoveSpeed", -2.0);
    pair<string, double> rt = std::make_pair("ReloadTime", +5.0e+3);
    snowEffect->addMiniEffect(mv);
    snowEffect->addMiniEffect(rt);
}

void GulakiUpgrade::releaseDamage(std::shared_ptr<SceneObject> aTarget)
{
    aTarget->getEffectReceiver()->applyEffect(snowEffect);
    int dmgPhysical = static_cast<int>(Enums::DamageTypes::dtPHYSICAL);
    aTarget->getDestructibleObject()->receiveDamageOneType(dmgPhysical, 20);
    affectedMobs->push_back(aTarget);
}

bool GulakiUpgrade::onReady(double timestep)
{
    if (target != nullptr)
    {

        auto monsters = parentScenePtr->findObjectsByTag("Monster");
        int counter = 0;
        int counterMax = 2;
        affectedMobs->clear();
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

bool GulakiUpgrade::onWorking(double timestep)
{
    return true;

}

bool GulakiUpgrade::onCooldown(double timestep)
{
    return true;
}

bool GulakiUpgrade::canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate)
{
    std::cout << "LALALA" << std::endl;
    MobAbility::setTarget(targ);
    return (targ != nullptr && aistate == Enums::AIMobStates::aiATTACK);
}

