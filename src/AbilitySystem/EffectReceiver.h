#pragma once

#include <memory>

#include "EffectModel.h"

class EffectReceiver
{
public:
    virtual ~EffectReceiver() = default;
    virtual bool applyEffect(std::shared_ptr<EffectModel> effect);
    virtual bool cancelEffect(std::shared_ptr<EffectModel> effect);
    virtual bool parseEffect(std::shared_ptr<EffectModel> effect, bool remove);
    virtual bool hasEffect(std::shared_ptr<EffectModel> effect) const;
    virtual void processTemporaryEffects(double);

protected:
    virtual bool parseMethod(list< pair<string, double> > & attributes, int removeFlag) = 0;

protected:
    list<std::shared_ptr<EffectModel>> effectsList;
};

