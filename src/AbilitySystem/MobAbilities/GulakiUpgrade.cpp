#include "GulakiUpgrade.h"

GulakiUpgrade::GulakiUpgrade(std::shared_ptr<ManaGlobal> aManaModel)
    : MobAbility(aManaModel)
    , affectedMobs(std::make_unique<std::list<std::shared_ptr<SceneObject> > >())
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
    affectedMobs->push_back(aTarget);
}

bool GulakiUpgrade::onReady(double /*timestep*/)
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
        int counterMax = 2;

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

bool GulakiUpgrade::onWorking(double /*timestep*/)
{
    return true;
}

bool GulakiUpgrade::onCooldown(double /*timestep*/)
{
    return true;
}

bool GulakiUpgrade::canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates aistate)
{
    MobAbility::setTarget(targ);
    return (targ != nullptr && targ->getTag() == "Monster" && aistate == Enums::AIMobStates::aiATTACK);
}
