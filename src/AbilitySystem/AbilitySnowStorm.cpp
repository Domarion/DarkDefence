#include "AbilitySnowStorm.h"
#include "../GlobalScripts/GameModel.h"
#include "../Grouping/Scene.h"

AbilitySnowStorm::AbilitySnowStorm(std::shared_ptr<ManaGlobal> aManaModel)
    : AbilityModel(aManaModel)
    , damagePerSecond(0)
{
}

void AbilitySnowStorm::init(std::shared_ptr<Scene> scenePtr)
{
    AbilityModel::init(scenePtr);

    pair<string, double> mv = std::make_pair("MoveSpeed", -2.0);
    pair<string, double> rt = std::make_pair("ReloadTime", +5.0e+3);
    snowEffect = std::make_shared<EffectModel>();
    snowEffect->addMiniEffect(mv);
    snowEffect->addMiniEffect(rt);
}

bool AbilitySnowStorm::onReady(double /*timestep*/)
{
    if (affectedMobs == nullptr && parentScenePtr != nullptr && GameModel::getInstance()->getMonsterCount() > 0)
        affectedMobs = parentScenePtr->findObjectsByTag("Monster");

    if (affectedMobs)
    {
        for(auto affectedMob = affectedMobs->begin(); affectedMob != affectedMobs->end(); ++affectedMob)
        {
            if (*affectedMob != nullptr)
                (*affectedMob)->getEffectReceiver()->applyEffect(snowEffect);
        }

        abilityState = Enums::AbilityStates::asWorking;
    }
    else
        abilityState = Enums::AbilityStates::asNotAvaliable;

    return true;
}

bool AbilitySnowStorm::onWorking(double timestep)
{

    if (counter >= 1000)
    {
        if (affectedMobs!= nullptr && affectedMobs->size() > 0)
            for(auto affectedMob = affectedMobs->begin(); affectedMob != affectedMobs->end(); ++affectedMob)
            {
                if (*affectedMob != nullptr)
                    (*affectedMob)->getDestructibleObject()->receiveDamageOneType(2, damagePerSecond);
            }
        counter = 0;
    }

    if (currentWorkTime <= 0)
    {
        if (affectedMobs!= nullptr && affectedMobs->size() > 0)
            for(auto affectedMob = affectedMobs->begin(); affectedMob != affectedMobs->end(); ++affectedMob)
            {
                if (*affectedMob != nullptr)
                    (*affectedMob)->getEffectReceiver()->cancelEffect(snowEffect);
            }

        currentWorkTime = workTime;
        affectedMobs.reset();

        abilityState = Enums::AbilityStates::asOnCooldown;
    }
    else
    {
        currentWorkTime -= timestep;
        counter += timestep;
    }

    return true;
}

void AbilitySnowStorm::setDamagePerSecond(int value)
{
    damagePerSecond = value;
}
