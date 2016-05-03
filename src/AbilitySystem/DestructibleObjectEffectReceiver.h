#pragma once
#include "../Mob/DestructibleObject.h"
#include "EffectReceiver.h"


class DestructibleObjectEffectReceiver: public EffectReceiver
{
public:
    DestructibleObjectEffectReceiver();
    virtual ~DestructibleObjectEffectReceiver();
    void init(DestructibleObject* const modelPtr);
protected:
    virtual bool parseMethod(list<pair<string, double> > &attributes, int removeFlag) override;

private:
    DestructibleObject* doModelPtr;
};
