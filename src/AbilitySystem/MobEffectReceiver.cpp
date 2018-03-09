#include <map>

#include "MobEffectReceiver.h"

void MobEffectReceiver::init(std::shared_ptr<MobModel> modelPtr)
{
    mobModelPtr = modelPtr;
}

bool MobEffectReceiver::parseMethod(list<pair<string, double> >& attributes, int removeFlag)
{
    if (mobModelPtr == nullptr)
        return false;

    for(auto attrib = attributes.begin(); attrib != attributes.end(); ++attrib)
    {
        double amount = removeFlag*attrib->second;
        if (attrib->first == "PhysicalDamage")
        {
            int newAmount = mobModelPtr->getAttackDamageModifier(0) + static_cast<int>(amount);
            mobModelPtr->setAttackDamageModifier(0, newAmount);
        }
        else if (attrib->first == "FireDamage")
        {
            int newAmount = mobModelPtr->getAttackDamageModifier(1) + static_cast<int>(amount);
            mobModelPtr->setAttackDamageModifier(1, newAmount);
        }
        else if (attrib->first == "ColdDamage")
        {
            int newAmount = mobModelPtr->getAttackDamageModifier(2) + static_cast<int>(amount);
            mobModelPtr->setAttackDamageModifier(2, newAmount);
        }
        else if (attrib->first == "PsyonicalDamage")
        {
            int newAmount = mobModelPtr->getAttackDamageModifier(3) + static_cast<int>(amount);
            mobModelPtr->setAttackDamageModifier(3, newAmount);
        }
        else if (attrib->first == "Protection")
        {
            int newAmount = mobModelPtr->getProtectionModifier() + static_cast<int>(amount);
            mobModelPtr->setProtectionModifier( newAmount );
        }
        else if (attrib->first == "MoveSpeed")
        {
            double newAmount = mobModelPtr->getMoveSpeedModifier() + amount;
            mobModelPtr->setMoveSpeedModifier( newAmount );
        }
        else if (attrib->first == "AttackDistance")
        {
            double newAmount = mobModelPtr->getAttackDistanceModifier() + amount;
            mobModelPtr->setAttackDistanceModifier( newAmount );
        }
        else if (attrib->first == "ReloadTime")
        {
            double newAmount = mobModelPtr->getReloadTimeMaximumModifier() + amount;
            mobModelPtr->setReloadTimeMaximumModifier( newAmount );
        }
        else if (attrib->first == "Stun")
        {
            mobModelPtr->setIsStunned(removeFlag == 1);

        }
    }
    return true;
}

void MobEffectReceiver::processTemporaryEffects(double aDeltaTime)
{
    if (effectsList.empty())
    {
        return;
    }

    for(auto effectIter = effectsList.begin(); effectIter != effectsList.end();)
    {
        if (*effectIter != nullptr && (*effectIter)->getDuration() > 0.0)
        {
            double runningTime = (*effectIter)->getRunningTime() + aDeltaTime;

            (*effectIter)->setRunningTime(runningTime);

            if (runningTime >= ((*effectIter)->getDuration()))
            {
                if (parseEffect((*effectIter), true))
                {
                    effectsList.erase(effectIter++);
                    continue;
                }
            }
        }

        ++effectIter;
    }
}
