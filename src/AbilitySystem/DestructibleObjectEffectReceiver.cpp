#include "DestructibleObjectEffectReceiver.h"
#include <iostream>

DestructibleObjectEffectReceiver::DestructibleObjectEffectReceiver()
{

}

DestructibleObjectEffectReceiver::~DestructibleObjectEffectReceiver()
{

}

void DestructibleObjectEffectReceiver::init(DestructibleObject * const modelPtr)
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
            std::cout << "protShouldBe ";
            int newAmount = doModelPtr->getProtectionModifier() + static_cast<int>(amount);
            doModelPtr->setProtectionModifier( newAmount );
            std::cout << (doModelPtr->getProtectionModifier()) << std::endl;

        }
    }

    return true;
}

