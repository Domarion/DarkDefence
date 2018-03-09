#pragma once

#include <memory>

#include "../Mob/DestructibleObject.h"
#include "EffectReceiver.h"

class DestructibleObjectEffectReceiver: public EffectReceiver
{
public:
    virtual ~DestructibleObjectEffectReceiver() =default;

    void init(std::shared_ptr<DestructibleObject> modelPtr);
protected:
    virtual bool parseMethod(list<pair<string, double> > &attributes, int removeFlag) override;

private:
    std::shared_ptr<DestructibleObject> doModelPtr;
};
