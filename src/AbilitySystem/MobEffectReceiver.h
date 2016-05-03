#pragma once
#include "EffectReceiver.h"
#include "../Mob/MobModel.h"

class MobEffectReceiver: public EffectReceiver
{
public:
    MobEffectReceiver();
    virtual ~MobEffectReceiver();
    void init(MobModel* const modelPtr);

protected:
    virtual bool parseMethod(list<pair<string, double> > &attributes, int removeFlag) override;

private:
    MobModel* mobModelPtr;

};
