#include "AbilityEarthquake.h"
#include "../GlobalScripts/GameModel.h"

AbilityEarthquake::AbilityEarthquake(std::shared_ptr<ManaGlobal> aManaModel)
    : AbilityModel(aManaModel)
    , damagePerSecond(0)
    , affectedMobs(nullptr)
    , stunEffect(std::make_shared<EffectModel>())
{
    pair<string, double> imbalizing = std::make_pair("Stun", 1);
    stunEffect->addMiniEffect(imbalizing);
    stunEffect->setCaption("Stun");
    stunEffect->setDuration(workTime);
}

bool AbilityEarthquake::onReady(double /*timestep*/)
{
    if (affectedMobs == nullptr && parentScenePtr != nullptr && GameModel::getInstance()->getMonsterCount() > 0)
        affectedMobs = parentScenePtr->findObjectsByTag("Monster");

    if (affectedMobs != nullptr)
    {
        for(auto affectedMob = affectedMobs->begin(); affectedMob != affectedMobs->end(); ++affectedMob)
        {
            if (*affectedMob != nullptr)
                (*affectedMob)->getEffectReceiver()->applyEffect(stunEffect);
        }

        abilityState = Enums::AbilityStates::asWorking;
    }
    else
        abilityState = Enums::AbilityStates::asNotAvaliable;

    return true;
}

bool AbilityEarthquake::onWorking(double timestep)
{
    if (counter >= 1000)
    {
        if (affectedMobs!= nullptr && !affectedMobs->empty())
            for(auto affectedMob = affectedMobs->begin(); affectedMob != affectedMobs->end(); ++affectedMob)
            {
                if (*affectedMob != nullptr)
                    (*affectedMob)->getDestructibleObject()->receiveDamageOneType(1, damagePerSecond);
            }

        counter = 0;
    }

    if (currentWorkTime <= 0)
    {

        currentWorkTime = workTime;
        abilityState = Enums::AbilityStates::asOnCooldown;

        if (affectedMobs!= nullptr && !affectedMobs->empty())
            for(auto affectedMob = affectedMobs->begin(); affectedMob != affectedMobs->end(); ++affectedMob)
            {
                if (*affectedMob != nullptr)
                    (*affectedMob)->getEffectReceiver()->cancelEffect(stunEffect);
            }
        affectedMobs->clear();
    }
    else
    {
        currentWorkTime -= timestep;
        counter+= timestep;
    }
    return true;
}

void AbilityEarthquake::setDamagePerSecond(int value)
{
    damagePerSecond = value;
}
