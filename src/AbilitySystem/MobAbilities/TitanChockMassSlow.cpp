#include "TitanChockMassSlow.h"
#include "Scenes/GameScene.h"

TitanChockMassSlow::TitanChockMassSlow(std::shared_ptr<ManaGlobal> aManaModel)
    : MobAbility(aManaModel)
    , affectedMobs(std::make_unique<std::list<std::shared_ptr<SceneObject> > >())
    , slowEffect(std::make_shared<EffectModel>())
{
    pair<string, double> mv = std::make_pair("MoveSpeed", -0.15);
    slowEffect->addMiniEffect(mv);
    slowEffect->setCaption("Titan chock mass slow");
}

bool TitanChockMassSlow::onReady(double /*timestep*/)
{
    affectedMobs->clear();

    auto monsters = parentScenePtr->findObjectsByTag("Monster");
    abilityState = Enums::AbilityStates::asNotAvaliable;

    if (monsters == nullptr)
    {
        return false;
    }

    for(auto& monster : *monsters)
    {
        if (monster != nullptr)
        {
            if (!monster->getEffectReceiver()->hasEffect(slowEffect))
            {
                monster->getEffectReceiver()->applyEffect(slowEffect);
            }
        }
    }

    return true;
}

bool TitanChockMassSlow::onWorking(double /*timestep*/)
{
    return true;
}

bool TitanChockMassSlow::onCooldown(double /*timestep*/)
{
    return true;
}

bool TitanChockMassSlow::canTrigger(std::shared_ptr<SceneObject> /*targ*/, Enums::AIMobStates /*aistate*/)
{
    return abilityState == Enums::AbilityStates::asNotAvaliable;
}
