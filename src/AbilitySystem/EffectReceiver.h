#pragma once
#include "EffectModel.h"
#include <memory>
class EffectReceiver
{
public:
    EffectReceiver() = default;
    virtual ~EffectReceiver() = default;
    virtual bool applyEffect(std::shared_ptr<EffectModel> effect);
    virtual bool cancelEffect(std::shared_ptr<EffectModel> effect);
    virtual bool parseEffect(std::shared_ptr<EffectModel> effect, bool remove);
    virtual bool hasEffect(std::shared_ptr<EffectModel> effect) const;
private:
    list<std::shared_ptr<EffectModel>> effectsList;
protected:
    virtual bool parseMethod(list< pair<string, double> > & attributes, int removeFlag) = 0;
};

