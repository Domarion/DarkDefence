#pragma once
#include "EffectModel.h"

class EffectReceiver
{
public:
    EffectReceiver();
    virtual ~EffectReceiver();
    virtual bool applyEffect(EffectModel* const effect);
    virtual bool cancelEffect(EffectModel* const effect);
    virtual bool parseEffect(EffectModel* const effect, bool remove);
    virtual bool hasEffect(EffectModel* const effect) const;
private:
    list<EffectModel*> effectsList;
protected:
    virtual bool parseMethod(list< pair<string, double> > & attributes, int removeFlag) = 0;
};

