#include "AbilityShrink.h"
#include "../GlobalScripts/GameModel.h"
AbilityShrink::AbilityShrink()
{

}

AbilityShrink::~AbilityShrink()
{

}

void AbilityShrink::init(Scene * const scenePtr)
{
    AbilityModel::init(scenePtr);
}

bool AbilityShrink::onReady(double timestep)
{
    if (affectedMobs.size() == 0 && parentScenePtr != nullptr && GameModel::getInstance()->getMonsterCount() > 0)
        affectedMobs = (parentScenePtr->findObjectsByTag("Monster"));

    if (affectedMobs.size() > 0)
    {
        abilityState = Enums::AbilityStates::asWorking;
        std::cout << "worked" << std::endl;
    }
    else
        abilityState = Enums::AbilityStates::asNotAvaliable;

    return true;
}

bool AbilityShrink::onWorking(double timestep)
{
    static double counter = 0.0;

    if (counter >= 1000)
    {
        if (affectedMobs.size() > 0)
            for(auto affectedMob = affectedMobs.begin(); affectedMob != affectedMobs.end(); ++affectedMob)
            {
                if (*affectedMob != nullptr && (*affectedMob)->getDestructibleObject() != nullptr)
                {
                    int damage = static_cast<int>((*affectedMob)->getDestructibleObject()->getMaximumHealth()*damagePerSecond);
                    (*affectedMob)->getDestructibleObject()->receiveDamageOneType(3, damage);
                }
            }
        counter = 0;
    }

    if (currentWorkTime <= 0)
    {
        currentWorkTime = workTime;
        abilityState = Enums::AbilityStates::asOnCooldown;
    }
    else
    {
        currentWorkTime -= timestep;
        counter+= timestep;
    }

    return true;
}

bool AbilityShrink::onCooldown(double timestep)
{
    if (currentCooldownTime <= 0)
    {
        affectedMobs.clear();
        currentCooldownTime = cooldownTime;
        abilityState = Enums::AbilityStates::asNotAvaliable;
    }
    else
        currentCooldownTime -= timestep;

    return true;
}

void AbilityShrink::setDamagePerSecond(double value)
{
    damagePerSecond = value;
}

double AbilityShrink::getDamagePerSecond() const
{
    return damagePerSecond;
}


/*	short formula = (short)(ef.getHealthMax()*DamageValuePerSecond);
                        //DebugMap.Instance.AddMessage("\nDamageValuePerSecond" + DamageValuePerSecond.ToString());
                        ef.ReceiveDamageOneType(formula,(byte)DamageTypes.Psionical,false);
                        */
