#include <algorithm>

#include "EffectReceiver.h"

bool EffectReceiver::applyEffect(std::shared_ptr<EffectModel> effect)
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

bool EffectReceiver::cancelEffect(std::shared_ptr<EffectModel> effect)
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

bool EffectReceiver::parseEffect(std::shared_ptr<EffectModel> effect, bool remove)
{
    int flag = remove? -1 : 1;
    if (effect == nullptr)
        return false;
    list<pair<string, double> > attributes = effect->getAffectedAttributes();

    return parseMethod(attributes, flag);
}

bool EffectReceiver::hasEffect(std::shared_ptr<EffectModel> effect) const
{
    auto findIter = std::find(effectsList.begin(), effectsList.end(), effect);
    return findIter != effectsList.end();
}

void EffectReceiver::processTemporaryEffects(double /*deltaTime*/)
{
}
