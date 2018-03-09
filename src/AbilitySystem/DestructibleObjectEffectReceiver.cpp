#include "DestructibleObjectEffectReceiver.h"

void DestructibleObjectEffectReceiver::init(std::shared_ptr<DestructibleObject> modelPtr)
{
    doModelPtr = modelPtr;
}

bool DestructibleObjectEffectReceiver::parseMethod(list<pair<string, double> > &attributes, int removeFlag)
{
    if (doModelPtr == nullptr)
        return false;

    for(auto attrib = attributes.begin(); attrib != attributes.end(); ++attrib)
    {
        double amount = removeFlag*attrib->second;

        if (attrib->first == "Protection")
        {
            int newAmount = doModelPtr->getProtectionModifier() + static_cast<int>(amount);
            doModelPtr->setProtectionModifier( newAmount );
        }
        else if (attrib->first == "Health")
        {
            int newAmount = doModelPtr->getMaximumHealth() + static_cast<int>(amount);
            doModelPtr->setMaximumHealth( newAmount );

        }
        else if (attrib->first == "ProtectionPercent")
        {
            int newAmount = static_cast<int>(doModelPtr->getProtectionModifier() * (1 + amount));
            doModelPtr->setProtectionModifier( newAmount );

        }
        else if (attrib->first == "HealthPercent")
        {
            int newAmount = static_cast<int>(doModelPtr->getMaximumHealth() * (1 + amount));
            doModelPtr->setMaximumHealth( newAmount );
        }
    }

    return true;
}

