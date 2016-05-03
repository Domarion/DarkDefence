#include "EffectModel.h"

EffectModel::EffectModel()
{

}

EffectModel::~EffectModel()
{

}

bool EffectModel::addMiniEffect(pair<string, double> &mini)
{
    affectedAttributes.push_back(mini);
}

bool EffectModel::removeMiniEffect(pair<string, double> &mini)
{
    affectedAttributes.remove(mini);
}

const list<pair<string, double> > &EffectModel::getAffectedAttributes() const
{
    return affectedAttributes;
}

string EffectModel::getCaption() const
{
    return caption;
}

void EffectModel::setCaption(const string &value)
{
    caption = value;
}

double EffectModel::getRunningTime() const
{
    return runningTime;
}

void EffectModel::setRunningTime(double value)
{
    runningTime = value;
}

void EffectModel::setDuration(double value)
{
    duration.first = value;
}

void EffectModel::setDurationModifier(double value)
{
    duration.second = value;
}

double EffectModel::getDuration() const
{
    return duration.first + duration.second;
}
