#include "EnemyInfo.h"

EnemyInfo::EnemyInfo(const string &aTag, EReaction aReaction, int aPriority)
    : tag(aTag)
    , reaction(aReaction)
    , priority(aPriority)
{
}

const std::string& EnemyInfo::getTag() const
{
    return tag;
}

void EnemyInfo::setTag(const string& aTag)
{
    tag = aTag;
}

EReaction EnemyInfo::getReaction() const
{
    return reaction;
}

void EnemyInfo::setReaction(EReaction aReaction)
{
    reaction = aReaction;
}

int EnemyInfo::getPriority() const
{
    return priority;
}

void EnemyInfo::setPriority(int aPriority)
{
    priority = aPriority;
}
