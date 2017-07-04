#include "MobEffectReceiver.h"
#include <map>
MobEffectReceiver::MobEffectReceiver()
    :EffectReceiver(), mobModelPtr(nullptr)
{

}


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
            double newAmount = mobModelPtr->getReloadTimeModifier() + amount;
            mobModelPtr->setReloadTimeModifier( newAmount );
            if (removeFlag == -1)
            {
                double oldAmount = mobModelPtr->getReloadTime() + amount;
                mobModelPtr->setReloadTime(oldAmount);
            }
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
//    std::cout << "Entered " << effectsList.size() << std::endl;


    if (effectsList.empty())
    {
        return;
    }

    for(auto effectIter = effectsList.begin(); effectIter != effectsList.end();)
    {
        if (*effectIter != nullptr && (*effectIter)->getDuration() > 0.0)
        {
//            std::cout << "Effect caption = " << effectPtr->getCaption() << std::endl;

            double runningTime = (*effectIter)->getRunningTime() + aDeltaTime;

            (*effectIter)->setRunningTime(runningTime);
            std::cout << "Effect running = " << runningTime << std::endl;

//            std::cout << "Effect duration = " << effectPtr->getDuration() << std::endl;

            if (runningTime >= ((*effectIter)->getDuration()))
            {
                std::cout << "Effect caption = " << (*effectIter)->getCaption() << std::endl;
                if (parseEffect((*effectIter), true))
                {
                    effectsList.erase(effectIter++);
                    continue;
                }
            }
        }

        ++effectIter;
    }

//    for(auto& effectPtr : effectsList)
//    {
//        if (effectPtr != nullptr && effectPtr->getDuration() > 0.0)
//        {
////            std::cout << "Effect caption = " << effectPtr->getCaption() << std::endl;

//            double runningTime = effectPtr->getRunningTime() + aDeltaTime;

//            effectPtr->setRunningTime(runningTime);
//            std::cout << "Effect running = " << runningTime << std::endl;

//            std::cout << "Effect duration = " << effectPtr->getDuration() << std::endl;

//            if (runningTime >= (effectPtr->getDuration()))
//            {
//                std::cout << "Effect caption = " << effectPtr->getCaption() << std::endl;
//                if (parseEffect(effectPtr, true))
//                {
//                    effectPtr.reset();
//                }
//            }
//        }
//    }

}
