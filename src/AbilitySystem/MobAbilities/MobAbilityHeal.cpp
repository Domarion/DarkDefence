#include "MobAbilityHeal.h"

bool MobAbilityHeal::onReady(double /*timestep*/)
{
    if (target != nullptr)
    {
        auto affectedMobs = parentScenePtr->findObjectsInRadius(target->getPosition(), 48 * 5);

        if (affectedMobs == nullptr)
        {
            abilityState = Enums::AbilityStates::asNotAvaliable;

            return false;
        }

        const double allowedPercentage = 0.80;

        const int maxMobs = 2;
        int counter = 0;
        const int regen = 50;

        for(auto& affectedMob : *affectedMobs)
        {
            if (affectedMob == nullptr
                    || affectedMob->getTag() != "Monster"
                    || !affectedMob->getDestructibleObject()
                    || !affectedMob->getDestructibleObject()->IsAlive())
            {
                continue;
            }

            double percentage = static_cast<double>(affectedMob->getDestructibleObject()->getCurrentHealth())
                / affectedMob->getDestructibleObject()->getMaximumHealth();

            if (percentage <= allowedPercentage)
            {
                target->getDestructibleObject()->addHealth(regen);

                if (++counter == maxMobs)
                {
                    abilityState = Enums::AbilityStates::asOnCooldown;
                    return true;
                }
            }
        }
    }

    abilityState = Enums::AbilityStates::asNotAvaliable;

    return true;
}

bool MobAbilityHeal::onWorking(double /*timestep*/)
{
    return true;
}

bool MobAbilityHeal::onCooldown(double timestep)
{
    if (currentCooldownTime <= 0)
    {
        currentCooldownTime = cooldownTime;
        abilityState = Enums::AbilityStates::asNotAvaliable;
    }
    else
        currentCooldownTime -= timestep;

    return true;
}

bool MobAbilityHeal::canTrigger(std::shared_ptr<SceneObject> targ, Enums::AIMobStates /*aistate*/)
{
    if (targ == nullptr || abilityState != Enums::AbilityStates::asNotAvaliable)
        return false;

    if (targ->getTag() != "Monster")
        return false;

    auto affectedMobs = parentScenePtr->findObjectsInRadius(targ->getPosition(), 48 * 5);

    if (affectedMobs == nullptr)
        return false;

    const double allowedPercentage = 0.80;

    const int maxMobs = 2;
    int counter = 0;
    for(auto& affectedMob : *affectedMobs)
    {
        if (affectedMob == nullptr
                || affectedMob->getTag() != "Monster"
                || !affectedMob->getDestructibleObject()
                || !affectedMob->getDestructibleObject()->IsAlive())
        {
            continue;
        }

        double percentage = static_cast<double>(affectedMob->getDestructibleObject()->getCurrentHealth())
            / affectedMob->getDestructibleObject()->getMaximumHealth();

        if (percentage <= allowedPercentage)
        {
            if (++counter == maxMobs)
            {
                MobAbility::setTarget(targ);
                return true;
            }
        }
    }

    return false;
}
