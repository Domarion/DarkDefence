#include "EffectReceiver.h"
#include <algorithm>
EffectReceiver::EffectReceiver()
{

}

EffectReceiver::~EffectReceiver()
{

}

bool EffectReceiver::applyEffect(EffectModel * const effect)
{
    if (effect == nullptr)
        return false;

    if (parseEffect(effect, false))
    {
        effectsList.push_back(effect);
        return true;
    }

    return false;
}

bool EffectReceiver::cancelEffect(EffectModel * const effect)
{
    if (effect == nullptr)
        return false;
    if (parseEffect(effect, true))
    {
        effectsList.remove(effect);
        return true;
    }

    return false;
}

bool EffectReceiver::parseEffect(EffectModel * const effect, bool remove)
{
    int flag = remove? -1 : 1;
    if (effect == nullptr)
        return false;
    list<pair<string, double> > attributes = effect->getAffectedAttributes();

    return parseMethod(attributes, flag);

}

bool EffectReceiver::hasEffect(EffectModel * const effect) const
{
    auto findIter = std::find(effectsList.begin(), effectsList.end(), effect);
    return findIter != effectsList.end();
}
